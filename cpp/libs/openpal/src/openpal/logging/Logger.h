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
#ifndef __LOGGER_H_
#define __LOGGER_H_

#include "LogEntry.h"
#include "LogFilters.h"

#include "openpal/util/Uncopyable.h"

namespace openpal
{

class LogRoot;

/**
* Interface that represents a distinct logger with a name and running level
*/
class Logger
{
	friend class LogRoot;

public:	

	void Log(const LogFilters& filters, char const* location, char const* message, int errorCode = -1);
	
	bool IsEnabled(const LogFilters& filters) const;	

private:

	Logger(LogRoot* pRoot);

	LogRoot* pRoot;	
};

}

#endif

