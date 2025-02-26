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


#ifndef SELF_ITEXT_TO_SPEECH_H
#define SELF_ITEXT_TO_SPEECH_H

#include "utils/IService.h"
#include "utils/Sound.h"
#include "SelfLib.h"

struct Voices;
struct Words;

enum AudioFormatType
{
	AF_OGG = 0,
	AF_WAV,                     //Currently used
	AF_FLAC
};

class SELF_API ITextToSpeech : public IService
{
public:
	RTTI_DECL();

	//! Types
	typedef Delegate<Sound *>				ToSoundCallback;
	typedef Delegate<Voices *>				GetVoicesCallback;
	typedef Delegate<Words *>				WordsCallback;
	typedef Delegate<std::string *>			StreamCallback;

	//! Construction
	ITextToSpeech( const std::string & a_ServiceId, AuthType a_AuthType = AUTH_BASIC ) : IService( a_ServiceId, a_AuthType )
	{}

	//! Request all the available voices to use with ITextToSpeech, the provided callback
	//! will be invoked with the results.
	virtual void GetVoices( GetVoicesCallback a_Callback ) = 0;
	//! Set the active voice to use
	virtual void SetVoice( const std::string & a_Voice ) = 0;
	//! Request the audio data in the specified format for the provided text.
	virtual void Synthesis( const std::string & a_Text, AudioFormatType a_eFormat, 
		Delegate<const std::string &> a_Callback, bool a_IsStreaming = false ) = 0;
	//! Request a conversion of text to speech, note if the speech is in the local cache
	//! then the callback will be invoked and NULL will be returned.
	virtual void ToSound( const std::string & a_Text, ToSoundCallback a_Callback ) = 0;
	//! Request a conversion of text to speech with a web-socket, invoking the callbacks 
	//! as the data is received.
	//! a_Callback will be invoked with the received waveform data in chunks. This callback
	//! is invoked with NULL when the stream is closed or disconnected.
	//! a_WordsCallback if provided will be invoked with word information as received.
	virtual void ToSound( const std::string & a_Text, StreamCallback a_Callback, 
		WordsCallback a_WordsCallback = WordsCallback() ) = 0;
};

struct SELF_API Voice : public ISerializable
{
	RTTI_DECL();

	std::string m_Name;
	std::string m_Language;
	std::string m_Gender;
	std::string m_URL;

	virtual void Serialize(Json::Value & json)
	{
		json["name"] = m_Name;
		json["language"] = m_Language;
		json["gender"] = m_Gender;
		json["url"] = m_URL;
	}

	virtual void Deserialize(const Json::Value & json)
	{
		m_Name = json["name"].asString();
		m_Language = json["language"].asString();
		m_Gender = json["gender"].asString();
		m_URL = json["url"].asString();
	}
};

struct SELF_API Voices : public ISerializable
{
	RTTI_DECL();

	std::vector< Voice > m_Voices;

	virtual void Serialize(Json::Value & json)
	{
		SerializeVector( "voices", m_Voices, json );
	}

	virtual void Deserialize(const Json::Value & json)
	{
		DeserializeVector( "voices", json, m_Voices );
	}
};

struct SELF_API Words : public boost::enable_shared_from_this<Words>
{
	//! Types
	typedef boost::shared_ptr<Words>		SP;
	typedef boost::weak_ptr<Words>			WP;

	Words(const std::string & a_Word, double a_StartTime, double a_EndTime) :
		m_Word(a_Word),
		m_StartTime(a_StartTime),
		m_EndTime(a_EndTime)
	{}

	~Words()
	{}

	std::string	m_Word;
	double		m_StartTime;
	double		m_EndTime;

	const std::string & GetWord() const
	{
		return m_Word;
	}

	double GetStartTime() 
	{
		return m_StartTime;
	}

	double GetEndTime()
	{
		return m_EndTime;
	}
};

#endif
