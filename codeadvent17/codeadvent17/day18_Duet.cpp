#include "day18_Duet.h"

#include <map>
#include <iostream>
#include <cctype>
#include <list>

class DuetThread
{
public:
    DuetThread(long long processID, const std::vector<Instruction>& instructions){
        pOutputQueue_ = nullptr;
        registers_["p"] = processID;
        instructions_ = instructions;
        sendCounter_ = 0;
        recvCounter_ = 0;
        programCounter_ = 0;        
        lastInstruction_ = nullptr;
        threadID_ = processID;
    }

    long long getThreadID() const {
        return threadID_;
    }

    void setOutputQueue(std::list<long long> *pOutputQueue) {
        pOutputQueue_ = pOutputQueue;
    }

    std::list<long long>* getInputQueue() {
        return &inputQueue_;
    }

    size_t getInputQueueLenght() const {
        return inputQueue_.size();
    }

    unsigned getSendCounter() const {
        return sendCounter_;
    }

    unsigned getRecvCounter() const {
        return recvCounter_;
    }

    const Instruction* getLastInstruction() const {
        return lastInstruction_;
    }

    void run() {
      Instruction *pIns = nullptr;
      while (0 <= programCounter_ && programCounter_ < instructions_.size()) {
        pIns = &instructions_[programCounter_];
        if (pIns->id == "snd") {
          pOutputQueue_->push_back(getRegValue(pIns->X));
          ++sendCounter_;
        } else if (pIns->id == "set") {
          registers_[pIns->X] = getRegValue(pIns->Y);
        } else if (pIns->id == "add") {
          registers_[pIns->X] = registers_[pIns->X] + getRegValue(pIns->Y);
        } else if (pIns->id == "mul") {
          registers_[pIns->X] = registers_[pIns->X] * getRegValue(pIns->Y);
        } else if (pIns->id == "mod") {
          registers_[pIns->X] = registers_[pIns->X] % getRegValue(pIns->Y);
        } else if (pIns->id == "rcv") {
            if (inputQueue_.size() > 0) {
                auto val = inputQueue_.front();
                inputQueue_.pop_front();
                registers_[pIns->X] = val;
                ++recvCounter_;
            }
            else
                break;
        }

        if (pIns->id == "jgz" && getRegValue(pIns->X) > 0) {
          programCounter_ += getRegValue(pIns->Y);
        } else
          ++programCounter_;
      }

      lastInstruction_ = pIns;
    }

  private:
    std::map<std::string, long long> registers_;
    std::list<long long> inputQueue_;
    std::list<long long> *pOutputQueue_;
    std::vector<Instruction> instructions_;
    unsigned sendCounter_;
    unsigned recvCounter_;
    size_t programCounter_;
    Instruction *lastInstruction_;
    long long threadID_;

    long long getRegValue(const std::string& Y) { 
        if (isalpha(Y[0]))
            return registers_[Y];
        return std::stoll(Y);
    };
};
//==========================================================================

int Duet::compute(std::istream &input)
{
    std::vector<Instruction> instructions = readInstructions(input);

    int lastPlayedSound = 0;
    std::map<std::string, long long> registers;
    int programCounter = 0;
    auto getValue = [&](const std::string& Y) { 
        if (isalpha(Y[0]))
            return registers[Y];
        return std::stoll(Y);
    };

    while (1) {
        std::cout << programCounter << '\t';
        Instruction *pIns = &instructions[programCounter];
        if (pIns->id == "snd") {
            lastPlayedSound = getValue(pIns->X);
            std::cout << "snd " << lastPlayedSound;
        }
        else if (pIns->id == "set") {
            registers[pIns->X] = getValue(pIns->Y);
            std::cout << "set " << pIns->X << " to " << getValue(pIns->Y);
        }
        else if (pIns->id == "add") {
            std::cout << "add " << pIns->X << " + " << getValue(pIns->Y);
            registers[pIns->X] = registers[pIns->X] + getValue(pIns->Y);
        }
        else if (pIns->id == "mul") {
            std::cout << "mul " << pIns->X << " * " << getValue(pIns->Y);
            registers[pIns->X] = registers[pIns->X] * getValue(pIns->Y);
        }
        else if (pIns->id == "mod") {
            std::cout << "mod " << pIns->X << " %% " << getValue(pIns->Y);
            registers[pIns->X] = registers[pIns->X] % getValue(pIns->Y);        
        }
        else if (pIns->id == "rcv" && getValue(pIns->X) > 0)
            break;

        if (pIns->id == "jgz" && getValue(pIns->X) > 0) {
            programCounter += getValue(pIns->Y);
            std::cout << "jump by " << getValue(pIns->Y);
        }
        else
            ++programCounter;

        std::cout << "  [";
        for (auto x : registers)
            std::cout << '(' << x.first << ':' << x.second <<"),";
        std::cout << "]";

        std::cout << '\n';
    }

    return lastPlayedSound;
}
//--------------------------------------------------------------

std::vector<Instruction> Duet::readInstructions(std::istream &input)
{
    std::string line;
    std::vector<Instruction> instructions;
    while (std::getline(input, line))
    {
        Instruction ins;

        size_t pos = line.find(' ');
        ins.id = line.substr(0, pos);

        size_t pos2 = line.find(' ', pos + 1);
        if (pos2 != std::string::npos)
        {
            ins.X = line.substr(pos+1, pos2-pos-1);
            ins.Y = line.substr(pos2+1);
        }
        else
            ins.X = line.substr(pos+1);

        instructions.emplace_back(ins);
    }

return instructions;
}
//--------------------------------------------------------------

int Duet::compute_pt2(std::istream& in)
{
    std::vector<Instruction> instructions = readInstructions(in);

    DuetThread thread0(0, instructions);
    DuetThread thread1(1, instructions);

    thread0.setOutputQueue(thread1.getInputQueue());
    thread1.setOutputQueue(thread0.getInputQueue());

    DuetThread *pCurrentThread = &thread0;

    auto isWaitig = [](const DuetThread* thread) {
            return (thread->getInputQueueLenght() == 0);
    };

    do {
        pCurrentThread->run();

        if (pCurrentThread->getThreadID() == 0)
            pCurrentThread = &thread1;
        else
            pCurrentThread = &thread0;
    } while (!isWaitig(&thread0) || !isWaitig(&thread1));

return thread1.getSendCounter();
}

std::stringstream Duet::test_input(R"(set i 31
set a 1
mul p 17
jgz p p
mul a 2
add i -1
jgz i -2
add a -1
set i 127
set p 735
mul p 8505
mod p a
mul p 129749
add p 12345
mod p a
set b p
mod b 10000
snd b
add i -1
jgz i -9
jgz a 3
rcv b
jgz b -1
set f 0
set i 126
rcv a
rcv b
set p a
mul p -1
add p b
jgz p 4
snd a
set a b
jgz 1 3
snd b
set f 1
add i -1
jgz i -11
snd a
jgz f -16
jgz a -19
)");
