#ifndef _SINGLETON_H
#define _SINGLETON_H

#include <iostream>
#include <pthread.h>

template <typename T>
class singleton
{
protected:
    singleton(){}
    virtual ~singleton(){}
    
public:
    static T* shared()
    {
        if(_pInstance == NULL)
        {
			pthread_mutex_lock(&_mutex);
			if(_pInstance == NULL)
			{
            	_pInstance = new T();
			}
			pthread_mutex_unlock(&_mutex);
        }
        return _pInstance;
    }
    
    void destory_instance()
    {
        if(_pInstance)
        {
			pthread_mutex_lock(&_mutex);
			if(_pInstance)
			{
				delete _pInstance;
            	_pInstance = NULL;
			}
			pthread_mutex_unlock(&_mutex);
        }
    }
private:
	singleton(const singleton&);
	const singleton& operator=(const singleton&);

private:
    static T* _pInstance;
	static pthread_mutex_t _mutex;
};

template<typename T>
T* singleton<T>::_pInstance = NULL;

template<typename T>
pthread_mutex_t singleton<T>::_mutex = PTHREAD_MUTEX_INITIALIZER;

#endif 
