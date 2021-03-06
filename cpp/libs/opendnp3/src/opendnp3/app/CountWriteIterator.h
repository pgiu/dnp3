/**
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#ifndef __COUNT_WRITE_ITERATOR_H_
#define __COUNT_WRITE_ITERATOR_H_


#include <openpal/container/WriteBuffer.h>
#include <openpal/serialization/ISerializer.h>

namespace opendnp3
{

// A facade for writing APDUs to an external buffer
template <class CountType, class WriteType>
class CountWriteIterator
{
public:

	static CountWriteIterator Null()
	{		
		return CountWriteIterator();
	}

	CountWriteIterator() : count(0), pSerializer(nullptr), pPosition(nullptr), isValid(false)
	{}

	CountWriteIterator(openpal::ISerializer<WriteType>& serializer, openpal::WriteBuffer& position) :
		count(0),
		pSerializer(&serializer),
		countPosition(position),
		pPosition(&position),
		isValid(position.Size() >= CountType::Size)
	{
		if(isValid)
		{
			position.Advance(CountType::Size);
		}
	}

	~CountWriteIterator()
	{
		if (isValid)
		{
			CountType::Write(countPosition, count);			
		}		
	}	

	bool Write(const WriteType& value)
	{
		if (isValid && pPosition->Size() >= pSerializer->Size())
		{
			pSerializer->Write(value, *this->pPosition);
			++count;
			return true;			
		}
		else
		{
			return false;
		}
	}

	bool IsValid() const
	{
		return isValid;
	}

private:

	typename CountType::Type count;
	openpal::ISerializer<WriteType>* pSerializer;

	bool isValid;

	openpal::WriteBuffer countPosition;  // make a copy to record where we write the count
	openpal::WriteBuffer* pPosition;
};

}

#endif
