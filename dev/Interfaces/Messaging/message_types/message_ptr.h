/*****************************************************************//**
 * \file   message_ptr.h
 * \brief  
 * 
 * \todo move this to a Block subsystem
 * 
 * \author kason
 * \date   March 2023
 *********************************************************************/
#include "internal_message_type.h"

template<typename T>
class Message_Ptr
{
public:
	Message_Ptr() :
		message(nullptr),
		uses(new unsigned int(0))
	{ }
	Message_Ptr(T* mess) :
		message(mess),
		uses(new unsigned int(1))
	{ }
	Message_Ptr(const Message_Ptr& obj)
	{
		message = obj.message;
		uses = obj.uses;
		if(message != nullptr)
		{
			(*uses)++;
		}
	}
	~Message_Ptr()
	{
		cleanup();
	}

	T* operator->() const
	{
		return this->message;
	}
	T& operator*() const
	{
		return this->message;
	}
	void operator=(const Message_Ptr& obj)
	{
		cleanup();
		this->message = obj.message;
		this->uses = obj.uses;
		if(obj.message != nullptr)
		{
			(*this->uses)++;
		}
	}
	T* get() const
	{
		return this->message;
	}

	template<typename Message_Type>
	Message_Type convert_type()
	{
		Message_Type new_message;
		if(this->message != nullptr)
		{
			new_message = *dynamic_cast<Message_Type*>(this->message);

		}

		return new_message;
	}

	template<typename Message_Type>
	bool instance_of()
	{
		return dynamic_cast<const Message_Type*>(this->message) != nullptr;
	}

	unsigned int count()
	{
		return *(uses);
	}

	using element_type = T;
private:
	T* message;
	unsigned int* uses;

	void cleanup()
	{
		(*uses)--;
		if((*uses) <= 0)
		{
			if(message != nullptr)
			{
				delete message;
				message = nullptr;
				delete uses;
			}
		}
	}
};