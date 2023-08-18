/*****************************************************************//**
 * \file   message_ptr.h
 * \brief  
 * 
 * \author kason
 * \date   March 2023
 *********************************************************************/
#include "internal_message_type.h"

/**
@brief A smart pointer class for managing objects of type T.
This class provides reference-counted ownership semantics for objects of type T.
It keeps track of the number of references to the managed object and automatically
deletes the object when the last reference goes out of scope.
@tparam T The type of the managed object.
*/
template<typename T>
class Message_Ptr
{
public:
	/**
	@brief Default constructor.
	Constructs a Message_Ptr object with a null pointer and initializes the reference count to zero.
	*/
	Message_Ptr() :
		message(nullptr),
		uses(new unsigned int(0))
	{ }
	/**
	@brief Constructor with an initial object pointer.
	Constructs a Message_Ptr object with the specified object pointer and initializes the reference count to one.
	@param mess A pointer to the object of type T to manage.
	*/
	Message_Ptr(T* mess) :
		message(mess),
		uses(new unsigned int(1))
	{ }
	/**
	@brief Copy constructor.
	Constructs a Message_Ptr object as a copy of another Message_Ptr object.
	The reference count is increased by one if the copied object pointer is not null.
	@param obj The Message_Ptr object to copy from.
	*/
	Message_Ptr(const Message_Ptr& obj)
	{
		message = obj.message;
		uses = obj.uses;
		if(message != nullptr)
		{
			(*uses)++;
		}
	}
	/**
	@brief Destructor.
	Decreases the reference count and deletes the managed object if the reference count reaches zero.
	*/
	~Message_Ptr()
	{
		cleanup();
	}
	/**
	@brief Arrow operator overload.
	Provides access to the managed object's member functions and data using the arrow operator.
	@return A pointer to the managed object.
	*/
	T* operator->() const
	{
		return this->message;
	}
	/**
	@brief Dereference operator overload.
	Provides access to the managed object's member functions and data using the dereference operator.
	@return A reference to the managed object.
	*/
	T& operator*() const
	{
		return this->message;
	}
	/**
	@brief Assignment operator overload.
	Assigns the value of another Message_Ptr object to this object.
	The reference count is updated accordingly, and the previous managed object is deleted if necessary.
	@param obj The Message_Ptr object to assign from.
	*/
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
	/**
	@brief Inequality operator overload.
	Checks if the managed object pointer is not equal to the specified object pointer.
	@param obj A pointer to an object of type T.
	@return True if the managed object pointer is not equal to obj, false otherwise.
	*/
	bool operator!=(T* obj)
	{
		return this->message != obj;
	}
	/**
	@brief Get the managed object pointer.
	Retrieves the pointer to the managed object.
	@return A pointer to the managed object.
	**/
	T* get() const
	{
		return this->message;
	}
	/**
	@brief Convert the managed object to a different type.
	Converts the managed object to a different type using dynamic_cast.
	Note that the conversion may fail if the object is not of the specified type.
	@tparam Message_Type The type to convert the managed object to.
	@return The converted object of type Message_Type.
	*/
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
	/**
	@brief Check if the managed object is an instance of a given type.
	Checks if the managed object is an instance of the specified type using dynamic_cast.
	@tparam Message_Type The type to check against.
	@return True if the managed object is an instance of Message_Type, false otherwise.
	*/
	template<typename Message_Type>
	bool instance_of()
	{
		return dynamic_cast<const Message_Type*>(this->message) != nullptr;
	}
	/**
	@brief Get the current reference count.
	Retrieves the current reference count of the managed object.
	@return The number of references to the managed object.
	*/
	unsigned int count()
	{
		return *(uses);
	}
	/**
	@brief Alias for the managed object type.
	Defines an alias for the type of the managed object.
	*/
	using element_type = T;
private:
	T* message; ///< Pointer to the managed object.
	unsigned int* uses; ///< Pointer to the reference count.
	/**
	 * @brief Clean up the managed object.
	 *
	 * Decreases the reference count and deletes the managed object if the reference count reaches zero.
	 */
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
				uses = nullptr;
			}
		}
	}
};
