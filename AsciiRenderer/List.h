/*********************************************************************
** Program Filename: List.h
** Author: Joshua Lim
** Date: 5/13/2021
** Description: Dynamic-growing array that handles dynamic allocation of elements. Alternative to vectors.
** Input: Generic elements
** Output: Dynamic array of elements
*********************************************************************/

#pragma once
#ifndef LIST_H_
#define LIST_H_
#include <cstddef>
#include <stdexcept>
template <class T>
class List
{
private:
    T *arr;
    int number_of_elements;
    void grow_array();
    void shift_right(T, int);
    void shift_left(int);
    void copy(T *start, T *end, T *destination);

public:
    int length;

    List(const List<T> &);
    List();
    List(int);
    ~List();
    int count() const;
    void add(T);
    void insert_at(T, int);
    void remove_at(int);
    void remove(T);
    T &operator[](int) const;
    void remove_all();
    void trim();
    List<T> &operator=(const List<T> &other);
};

/*********************************************************************
** Function: List
** Description: constructor of List
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
template <class T>
List<T>::List()
{
    arr = new T();
    length = 0;
    number_of_elements = 0;
}

/*********************************************************************
** Function: List
** Description: copy constructor of List
** Parameters: other copy
** Pre-Conditions: copy
** Post-Conditions: none
*********************************************************************/
template <class T>
List<T>::List(const List<T> &other)
{
    length = other.length;
    //cout << "In List :: copying: " << &other << " to: " << this <<endl;
    number_of_elements = other.number_of_elements;
    arr = new T[length];
    //cout << "Arr: " << other.arr << endl;
    for (int i = 0; i < length; i++)
    {
        arr[i] = other.arr[i];
    }
}

/*********************************************************************
** Function: List
** Description: constructor of List
** Parameters: Takes in initial array size
** Pre-Conditions: int
** Post-Conditions: none
*********************************************************************/
template <class T>
List<T>::List(int size)
{
    //cout << "In List :: creating: " << this << endl;
    arr = new T[size];
    //cout << "In List :: creating ARR: " << arr << endl;
    length = size;
    number_of_elements = 0;
}

/*********************************************************************
** Function: ~List
** Description: destructor of List
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
template <class T>
List<T>::~List()
{
    //cout << "In List :: deleting: " << this <<"Arr: "<<arr<< endl;
    delete[] arr;
}

/*********************************************************************
** Function: grow_array
** Description: grows array by twice
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
template <class T>
void List<T>::grow_array()
{

    int newSize = length > 0 ? length * 2 : 1;
    T *temp = new T[newSize];
    if (length > 0)
    {
        copy(arr, arr + length, temp);
    }

    if (length > 0)
    {
        delete[] arr;
    }
    else
    {
        delete arr;
    }

    length = newSize;

    arr = temp;
}

/*********************************************************************
** Function: add
** Description: Adds element to array, pass by pointer
** Parameters: T* generic element
** Pre-Conditions: T*
** Post-Conditions: none
*********************************************************************/
template <class T>
void List<T>::add(T dt)
{
    number_of_elements++;
    if (number_of_elements > length)
    {
        grow_array();
    }
    arr[number_of_elements - 1] = dt;
}

/*********************************************************************
** Function: operator
** Description: assignment operator
** Parameters: none
** Pre-Conditions: copy other
** Post-Conditions: copy other
*********************************************************************/
template <class T>
List<T> &List<T>::operator=(const List<T> &other)
{
    length = other.length;
    //cout << "In List :: copying: " << &other << " to: " << this << endl;
    number_of_elements = other.number_of_elements;

    if (arr != NULL)
    {
        if (length > 1)
        {
            delete[] arr;
        }
        else
        {
            delete arr;
        }
        arr = NULL;
    }

    arr = new T[length];

    //cout << "Other Arr: " << other.arr << "To Arr: "<< arr <<endl;
    for (int i = 0; i < length; i++)
    {
        arr[i] = other.arr[i];
    }
    return *this;
}

/*********************************************************************
** Function: shift_right
** Description: Shifts array to the right starting at index traversing to right by recursion
** Parameters: int starting index, previous generic element
** Pre-Conditions: T*, int
** Post-Conditions: none
*********************************************************************/
template <class T>
void List<T>::shift_right(T previousElement, int index)
{
    if (index > length - 1)
    {
        return;
    }
    T temp = arr[index];
    arr[index] = previousElement;
    shift_right(temp, index + 1);
}

/*********************************************************************
** Function: shift_left
** Description: Shifts array to the left starting at index traversing to right
** Parameters: int starting index
** Pre-Conditions: int
** Post-Conditions: none
*********************************************************************/
template <class T>
void List<T>::shift_left(int index)
{
    if (index > length - 1)
    {
        return;
    }
    if (index + 1 > length - 1)
    {
        arr[index] = NULL;
        return;
    }
    else
    {
        arr[index] = arr[index + 1];
    }
    shift_left(index + 1);
}

/*********************************************************************
** Function: insert_at
** Description: Inserts element at specific index
** Parameters: pointer T*, int index
** Pre-Conditions: T*, int
** Post-Conditions: none
*********************************************************************/
template <class T>
void List<T>::insert_at(T dt, int index)
{
    number_of_elements++;
    if (number_of_elements >= length)
    {
        grow_array();
    }
    shift_right(NULL, index);
    arr[index] = dt;
}

/*********************************************************************
** Function: remove
** Description: Removes a specific element in array, DOES NOT FREE MEMORY
** Parameters: pointer T
** Pre-Conditions: T*
** Post-Conditions: none
*********************************************************************/
template <class T>
void List<T>::remove_at(int index)
{
    number_of_elements--;
    arr[index] = NULL;
    shift_left(index);
}

/*********************************************************************
** Function: remove
** Description: Removes a specific element in array, DOES NOT FREE MEMORY
** Parameters: pointer T
** Pre-Conditions: T*
** Post-Conditions: none
*********************************************************************/
template <class T>
void List<T>::remove(T dt)
{
    number_of_elements--;
    int i;
    for (i = 0; i < length; i++)
    {
        if (dt == arr[i])
        {
            break;
        }
    }
    arr[i] = NULL;
    shift_left(i);
}

/*********************************************************************
** Function: remove_all
** Description: Removes all elements in array, DOES NOT FREE MEMORY
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
template <class T>
void List<T>::remove_all()
{
    for (int i = 0; i < number_of_elements; i++)
    {
        arr[i] = NULL;
    }
    number_of_elements = 0;
    trim();
}

/*********************************************************************
** Function: trim
** Description: Cuts the size of array down to the number of elements in array
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
template <class T>
void List<T>::trim()
{
    if (number_of_elements != 0)
    {
        T *temp = new T[number_of_elements];
        if (length > 0)
        {
            copy(arr, arr + length, temp);
        }
        length = number_of_elements;
        delete[] arr;
        arr = temp;
    }
    else
    {
        delete[] arr;
        arr = new T();
    }
}

/*********************************************************************
** Function: operator[]
** Description: operator overload[] return element at [i]
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: T*
*********************************************************************/
template <class T>
T &List<T>::operator[](int index) const
{
    if (index > length)
    {
        throw std::out_of_range("Index out of range!");
    }
    else
    {
        return arr[index];
    }
}

/*********************************************************************
** Function: count
** Description: returns the number of elements in the list
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: int
*********************************************************************/
template <class T>
int List<T>::count() const
{
    return number_of_elements;
}

/*********************************************************************
** Function: copy
** Description: Copies array elements to another array
** Parameters: starting point, ending point, destination
** Pre-Conditions: starting point, ending point, destination
** Post-Conditions: list
*********************************************************************/
template <class T>
void List<T>::copy(T *start, T *end, T *destination)
{
    while (start != end)
    {
        *destination = *start;
        ++start;
        ++destination;
    }
}

#endif