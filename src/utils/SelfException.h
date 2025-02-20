/**
* Copyright 2017 IBM Corp. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/


#ifndef SELF_EXCEPTION_H
#define SELF_EXCEPTION_H

//! Class for exceptions throw by the SELF 
class SelfException 
{
public:
	SelfException( const char * a_pMessage )
	{
		m_pMessage = a_pMessage;
	}

	const char * Message() const
	{
		return m_pMessage;
	}

private:
	const char * m_pMessage;
};

#endif
