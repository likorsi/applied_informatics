#include <iostream>

template<typename T>
class safe_c_array_t
{
private:
	T* arr{};
	int size;
public:

	// конструктор без параметров
	safe_c_array_t()
	{
		size = 0;
		arr = nullptr;
	}

	// конструктор с параметрами
	safe_c_array_t(int size_of_array)
	{
		size = size_of_array;
		arr = new T[size];
		for (int i = 0; i < size; i++)
			arr[i] = 0;
	}

	// деструктор
	~safe_c_array_t()
	{
		delete[] arr;
	}

	// перегрузка []
	T& operator[](int i)
	{
		return arr[i];
	}

	// перегрузка оператора присваивания
	safe_c_array_t& operator=(safe_c_array_t& arr2)
	{
		size = arr2.size;
		arr = new T[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = arr2.arr[i];
		}
		return *this;
	}

};

int main()
{
	safe_c_array_t<int> arr(5);
	safe_c_array_t<float> arr2(10);
	safe_c_array_t<int> arr3(8);
	arr[0] = 10;
	arr2[0] = 4.78;
	arr3 = arr;

	for (size_t i = 0; i < 4; i++)
		std::cout << arr[i] << ' ';

	arr = arr;

	for (size_t i = 0; i < 4; i++)
		std::cout << arr[i] << ' ';

	std::cout << arr2[0] << '\n';
	std::cout << arr3[0] << '\n';

	return 0;
}
