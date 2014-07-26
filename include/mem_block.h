#ifndef _MEM_BLOCK_H
#define _MEM_BLOCK_H

#include <string.h>

class mem_block
{
	public:
		mem_block(char* pstr, int size)
			: _size(size)
		{
			_pstr = (char*)malloc(size);
			memcpy(_pstr, pstr, size);
		}
		mem_block(const mem_block& rhs)
			: _size(rhs._size)
		{
			_pstr = (char*)malloc(rhs._size);
			memcpy(_pstr, rhs._pstr, rhs._size);
		}
		mem_block& operator=(const mem_block& rhs)
		{
			if(&rhs == this)
				return *this;
			
			_size = rhs._size;
			_pstr = (char*)malloc(rhs._size);
			memcpy(_pstr, rhs._pstr, rhs._size);
		}

		~mem_block()
		{
			free(_pstr);
		}
		char* _pstr;
		int _size;
};

#endif
