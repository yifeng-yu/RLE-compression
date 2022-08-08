#include "RleData.h"
#include <iostream>

void RleData::Compress(const std::vector<int8_t>& input)
{
	// TODO
    mData.clear();
    std::vector<int8_t> tempVector;
    for(size_t currIndex = 0; currIndex < input.size(); currIndex++){
        int count = 1;
        while(currIndex + 1 < input.size() && input[currIndex] == input[currIndex+1] && count < 127){
            count++;
            currIndex++;
            
        }
//        if(count > 127){
//            tempVector.push_back(127);
//            tempVector.push_back(input[currIndex]);
//            count -= 127;
//        }
        tempVector.push_back(count);
        tempVector.push_back(input[currIndex]);
        
    }
//    for(size_t i = 0; i < tempVector.size(); i++){
//        std::cout << (int)tempVector[i] << " ";
//    }
    bool isValid = false;
    int i = 0;

    std::vector<int8_t> uniqueVector;
    while(i < tempVector.size() - 1){
        uint8_t runSize = tempVector[i];
        int8_t currElement = tempVector[i+1];
//        std::cout << static_cast<int>(runSize) << std::endl;
        while(runSize == 1 && (i+1) < tempVector.size()){

            uniqueVector.push_back(currElement);
            if(uniqueVector.size() + 1 > 127){
                
                mData.push_back(uniqueVector.size() * (-1));
                for(int j = 0; j < uniqueVector.size(); j++){
//                    std::cout << uniqueVector[j] << " ";
                    mData.push_back(uniqueVector[j]);
                }
//                std::cout << std::endl;
                uniqueVector.clear();
            }
            i = i + 2;
            // means no next element left in temp vector
            if(i >= tempVector.size()){
                break;
            }
            runSize = tempVector[i];
            currElement = tempVector[i+1];
        }
       
        // means the runsize exceeds the max
        // when run size is exceeding 127 e.g 128 -> -128
        // when run size is 130 ->
//        if(runSize < -127){
//            mData.push_back(127);
//            mData.push_back(currElement);
//            tempVector[i] *= -1;
//            tempVector[i] -= 127;
//            continue;
//
//        }
        
        if(runSize > 127){
            mData.push_back(127);
            mData.push_back(currElement);
            tempVector[i] -= 127;
            continue;
        }
        // repeat pattern/no unique
        if(uniqueVector.empty()){
            // read in additional extra parts exceeding 127
            if(i < tempVector.size()){
                mData.push_back(tempVector[i]);
                mData.push_back(tempVector[i+1]);
                i = i+2;
            }

        }
        else {
            if(uniqueVector.size() == 1){
                mData.push_back(1);
                mData.push_back(uniqueVector[0]);
                uniqueVector.clear();
            }
            else {
                mData.push_back(uniqueVector.size() * (-1));
                for(int j = 0; j < uniqueVector.size(); j++){
                    mData.push_back(uniqueVector[j]);
                }
                uniqueVector.clear();
            }
        }

    }
    
    
}


void RleData::Decompress(const std::vector<int8_t>& input, size_t outSize)
{
	// TODO
    mData.clear();
    std::vector<int8_t> output;
    output.reserve(outSize);
    int currIndex = 0;
    while (currIndex < input.size())
    {
        int runSize = input[currIndex];
        int nextIndex = currIndex + 1;
        // if we have positive run size, which means they are not unique runs
        if (runSize > 0)
        {
            for (int j = 0; j < runSize; j++){
                size_t next = input[nextIndex];
                output.push_back(next);

            }
            currIndex = currIndex + 2;
        }
        
        // negative means they are unique numbers
        else if (runSize < 0){
            runSize = runSize * (-1);
            for (int j = 0; j < runSize; j++){
                output.push_back(input[nextIndex + j]);
            }
            currIndex = currIndex + runSize + 1;
        }
    }

    for (size_t i = 0; i < output.size(); i++)
    {
        mData.push_back(output[i]);
    }
}

std::ostream& operator<< (std::ostream& stream, const RleData& rhs)
{
	for (size_t i = 0; i < rhs.mData.size(); i++)
	{
		stream << rhs.mData[i];
	}
	return stream;
}
