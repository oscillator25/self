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


#ifndef SELF_TOUCHSENSOR_H
#define SELF_TOUCHSENSOR_H

#include "SelfInstance.h"
#include "ISensor.h"
#include "TouchData.h"

#include "utils/ThreadPool.h"
#include "utils/Time.h"

#include "SelfLib.h"

//! Base class for a Touch Sensor class
class SELF_API TouchSensor : public ISensor
{
public:
	RTTI_DECL();

	//! Types
	typedef std::vector<IConditional::SP>		Conditions;

	struct TouchTranslation : public ISerializable
	{
		RTTI_DECL();

		//! ISerializable interface
		virtual void Serialize(Json::Value & json);
		virtual void Deserialize(const Json::Value & json);

		Conditions				m_Conditions;			// conditions to translate touch types
		std::string				m_TouchType;			// touch response from translation
	};


	TouchSensor() : ISensor("TouchSensor")
	{}

	//! ISerialiazable interface
	virtual void Serialize(Json::Value & json);
	virtual void Deserialize(const Json::Value & json);

	//! ISensor interface
	virtual const char * GetDataType()
	{
		return "TouchData";
	}

	virtual bool OnStart();
	virtual bool OnStop();
	virtual void OnPause();
	virtual void OnResume();
	
protected:
	//! Types
	typedef std::vector<TouchTranslation>	TouchTranslations;

	//! Data
	TouchTranslations	m_TouchTranslations;
};

#endif	// SELF_TOUCHSENSOR_H