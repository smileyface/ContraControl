template<typename T>
class Shared_Ptr
{
public:
	Shared_Ptr() :
		ptr(nullptr),
		reference_count(new char(0))
	{ }
	~Shared_Ptr()
	{
		cleanup();
	}
	Shared_Ptr(T* ptr) :
		ptr(ptr),
		reference_count(new char(1))
	{ }

	/**
	 * Copy constructor.
	 * \param obj Object to copy.
	 */
	Shared_Ptr(const Shared_Ptr& obj)
	{
		this->ptr = obj.ptr;
		this->reference_count = obj.reference_count;
		if(obj.ptr != nullptr)
		{
			(*this->reference_count)++;
		}
	}
	Shared_Ptr(Shared_Ptr&& dyingObj)
	{
		this->ptr = dyingObj.ptr; // share the underlying pointer
		this->reference_count = dyingObj.reference_count; // share refCount
	}
	T* get() const
	{
		return this->ptr;
	}

	void operator=(const Shared_Ptr& obj)
	{
		cleanup();

		this->ptr = obj.ptr;
		this->reference_count = obj.reference_count;
		if(obj.ptr != nullptr)
		{
			(*this->reference_count)++;
		}
	}
	void operator=(Shared_Ptr&& dyingObj) // move assignment
	{
		cleanup(); // cleanup any existing data

		this->ptr = dyingObj.ptr; // share the underlying pointer
		this->reference_count = dyingObj.reference_count;

		dyingObj.ptr = nullptr;
		dyingObj.reference_count = nullptr; // clean the dying object
	}
	T* operator->() const
	{
		return this->ptr;
	}
	T& operator*() const
	{
		return this->ptr;
	}
	bool operator!=(const Shared_Ptr& rhs) const
	{
		return this->ptr != rhs.ptr;
	}
	bool operator<(const Shared_Ptr& rhs) const
	{
		return this->ptr < rhs.ptr;
	}
	using element_type = T;
private:
	T* ptr = nullptr;
	char* reference_count = nullptr;

	void cleanup()
	{
		(*reference_count)--;
		if(*reference_count <= 0)
		{
			if(ptr != nullptr)
			{
				delete ptr;
			}
			delete reference_count;
		}
	}
};


template< class T, class U >
Shared_Ptr<T> dynamic_pointer_cast(const Shared_Ptr<U>& r) noexcept
{
	if(auto p = dynamic_cast<typename Shared_Ptr<T>::element_type*>(r.get()))
		return Shared_Ptr<T>({p});
	else
		return Shared_Ptr<T>();
}