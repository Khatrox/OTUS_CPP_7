//
// Created by xMellox on 11-Sep-20.
//
#include <gtest/gtest.h>
#include <BulkParser.h>
#include <OutputBulk.h>
#include <OutputBulkInFile.h>
#include <sys/stat.h>
#include <chrono>

void passInput(BulkParser& bulkParser, const std::list<std::string>& input)
{
    for(const auto& i : input)
    {
        bulkParser.passInput(i);
    }
}

bool exist_file(const std::string& name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

struct FirstCmdListener : BulkListener
{
    explicit FirstCmdListener(BulkSubject& bulkSubject)
    {
        bulkSubject.subscribe(*this);
    }

    void notifyExecute(const std::string& cmd) override
    {
            if(correct_name.empty())
            {
                correct_name += "bulk";
                const auto now = std::chrono::system_clock::now().time_since_epoch();
                const auto time = std::chrono::duration_cast<std::chrono::seconds>(now).count();
                correct_name += std::to_string(time);
            }
    }

    void notifyEnd() override
    {

    }

    std::string getCorrectName() const
    {
        return correct_name;
    }

private:
    std::string correct_name;
};

struct OtusTaskChecker :  BulkListener
{
    OtusTaskChecker(std::size_t cmdsPerBulk,std::list<std::string>& p_input, std::list<std::string>& p_correctBulks)
    :
    bulkParser{cmdsPerBulk},
    ss{},
    outputBulk{bulkParser.getBulk(),ss},
    outputBulkInFile{bulkParser.getBulk()},
    correctBulks{p_correctBulks},
    firstCmdListener{bulkParser.getBulk()},
    it{std::begin(correctBulks)},
    start{}
    {
        bulkParser.getBulk().subscribe(*this);
        passInput(bulkParser,p_input);
    }

    void notifyExecute(const std::string& cmd) override
    {

    }

    void notifyEnd() override
    {
        if (it != std::end(correctBulks))
        {
            std::string outputBulkStr = "bulk: ";
            outputBulkStr += *it;

            auto stream_str = ss.str();
            auto end = stream_str.find_first_of('\n',start);
            end += 1;
            auto check_str = stream_str.substr(start,end - start);
            start = end;

            ASSERT_STREQ(outputBulkStr.c_str(), check_str.c_str());


            const auto fileName = outputBulkInFile.getPathLastFile();
            ASSERT_EQ(exist_file(fileName), true);

            std::ifstream file{fileName};
            std::string content;
            std::getline(file,content);
            content += '\n';

            ASSERT_STREQ(content.c_str(), it->c_str());

            ++it;
        }
    }

private:
    BulkParser bulkParser;
    std::stringstream ss;
    OutputBulk outputBulk;
    OutputBulkInFile outputBulkInFile;
    FirstCmdListener firstCmdListener;

    std::list<std::string>& correctBulks;
    std::list<std::string>::iterator it;

    std::size_t start;
};



TEST(OutputBulk,BulksPerTwoCmds)
{
    BulkParser bulkParser{2};
    std::stringstream ss;
    OutputBulk outputBulk{bulkParser.getBulk(), ss};
    OutputBulkInFile outputBulkInFile{bulkParser.getBulk()};

    std::list<std::string> input
            {
                    "cmd1",
                    "cmd2",
                    "cmd3",
                    "cmd4",
                    "cmd5"
            };

    passInput(bulkParser,input);

    ASSERT_STREQ("bulk: cmd1, cmd2\n"
                     "bulk: cmd3, cmd4\n", ss.str().c_str());
}

TEST(OutputBulkInFile,FileCreated)
{
    BulkParser bulkParser{2};
    OutputBulkInFile outputBulkInFile{bulkParser.getBulk()};

    std::list<std::string> input
            {
                    "cmd1",
                    "cmd2"
            };

    passInput(bulkParser,input);
    const auto fileName = outputBulkInFile.getPathLastFile();

    ASSERT_EQ(exist_file(fileName), true);
}

TEST(OutputBulkInFile,FileContainsCmds)
{
    BulkParser bulkParser{2};
    OutputBulkInFile outputBulkInFile{bulkParser.getBulk()};

    std::list<std::string> input
            {
                    "cmd1",
                    "cmd2"
            };

    passInput(bulkParser,input);
    const auto fileName = outputBulkInFile.getPathLastFile();
    ASSERT_EQ(exist_file(fileName), true);

    std::ifstream file{fileName};
    std::string content;
    std::getline(file,content);

    ASSERT_STREQ(content.c_str(), "cmd1, cmd2");
}

TEST(OutputBulkInFile,FileNameCorrect)
{
    BulkParser bulkParser{2};
    OutputBulkInFile outputBulkInFile{bulkParser.getBulk()};
    FirstCmdListener firstCmdListener{bulkParser.getBulk()};

    std::list<std::string> input
            {
                    "cmd1",
                    "cmd2"
            };

    passInput(bulkParser,input);
    const auto fileName = outputBulkInFile.getPathLastFile();
    ASSERT_STREQ(fileName.c_str(), firstCmdListener.getCorrectName().c_str());
}

TEST(OtusSimpleCase, TwoBulksPerThreeCmds)
{
    BulkParser bulkParser{3};
    std::list<std::string> input
            {
                    "cmd1",
                    "cmd2",
                    "cmd3",
                    "cmd4",
                    "cmd5",
                    "cmd6"
            };

    std::list<std::string> correctBulks
    {
        "cmd1, cmd2, cmd3\n", "cmd4, cmd5, cmd6\n"
    };

    OtusTaskChecker otusTaskChecker{3,input, correctBulks};
}

TEST(OtusSimpleCase,FiveBulksPerTwoCmds)
{
    std::list<std::string> input
            {
                    "cmd1",
                    "cmd2",
                    "cmd3",
                    "cmd4",
                    "cmd5",
                    "cmd6",
                    "cmd7",
                    "cmd8",
                    "cmd9",
                    "cmd10",
                    "cmd11"
            };


    std::list<std::string> correctBulks
    {
        "cmd1, cmd2\n",
        "cmd3, cmd4\n",
        "cmd5, cmd6\n",
        "cmd7, cmd8\n",
        "cmd9, cmd10\n"
    };

    OtusTaskChecker otusTaskChecker{2, input, correctBulks};
}


TEST(OtusSimpleCase,DynamicBulk)
{
    std::list<std::string> input
            {
                    "cmd1",
                    "cmd2",
                    "{",
                    "cmd3",
                    "cmd4",
                    "cmd5",
                    "}"
            };


    std::list<std::string> correctBulks
            {
                    "cmd1, cmd2\n",
                    "cmd3, cmd4, cmd5\n"
            };

    OtusTaskChecker otusTaskChecker{2, input, correctBulks};
}

TEST(OtusSimpleCase,DynamicBulkAccidentallyEnd)
{
    std::list<std::string> input
            {
                    "cmd1",
                    "cmd2",
                    "{",
                    "cmd3",
                    "cmd4",
                    "cmd5"
            };


    std::list<std::string> correctBulks
            {
                    "cmd1, cmd2\n",
            };

    OtusTaskChecker otusTaskChecker{2, input, correctBulks};
}

TEST(OtusSimpleCase,IgnoreIncludedScopes)
{
    std::list<std::string> input
            {
                    "cmd1",
                    "cmd2",
                    "{",
                    "cmd3",
                    "{",
                    "cmd4",
                    "cmd5",
                    "}",
                    "cmd6",
                    "}"
            };


    std::list<std::string> correctBulks
            {
                    "cmd1, cmd2\n",
                    "cmd3, cmd4, cmd5, cmd6\n"
            };

    OtusTaskChecker otusTaskChecker{2, input, correctBulks};
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}