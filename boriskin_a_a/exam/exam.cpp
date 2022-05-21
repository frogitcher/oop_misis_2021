//#include "exam.h"
#include <stexcept>
#include <_INITIALIZER_LIST_>

Class set
{
  set() 
    _size()
    _capacity()
    _data()
  {}
  
  set(int size)
    _size(size)
    _capacity(size*2)
  {}

  set(__cpp_initializer_lists)
    _size = (__cpp_initializer_lists.Size())
    _capacity = (_size*2)
    {
      std::fill(__cpp_initializer_lists.Begin(), __cpp_initializer_lists.End(), _data);
    }

  ~set=default;

  set::operator=(const rhs) const
  {
    _size = rhs.Size();
    
  }

  set::operator==(const rhs)
  {

  }
  set::operator[](int index)
  {
    return _data[index];
  }

  set::operator!=(const rhs)
  {
    return !(rhs == this)
  }
  bool set::Empty()
  {
    if (_size == 0)
    {
      return True;
    }
    else
    {
      return False;
    }
  }

  int set::Size()
  {
    return _size;
  }

  void set::Insert(int index, int element)
  {
    for (int i = 0; i < _size; ++i)
    {
      if (element == _data[i])
      {
        std::throw_exception("Set has element like that");
      }
    }

    _size++;
    for (int i = index; i < _size; ++i)
    { 
      //_data[i] = _data[i+1]
    }
      
  }

  bool set::Find(int element)
  {
    for (int i=0; i<_size; ++i)
    {
      if (element == _data[i])
      {
        return True;
      } 
    }
    return False;
  }
  
  *int set::Begin()
  {
    return _data;
  }

  *int set::End()
  {
    return _data + _size;
  }

  void set::Copy(const int rhs) const
  {
    if (rhs.Size() < _size)
    {
      _size = rhs.Size();
    }
    
    else
    {
      std::copy(_data, _data+_size, _data);
    }
  }
  
  private:
  {
    int _size;
    int _capacity;
    int* _data;
  } 
}