#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

float func(float x)
{
    //return -x * log(x);
    //return - x * x - 0.5;
    //return sqrt(x);
}

int find_zero_line(std::vector<float> arr_values_y, int y)
{
    float y_min = *std::min_element(arr_values_y.begin(), arr_values_y.end());
    float y_max = *std::max_element(arr_values_y.begin(), arr_values_y.end());
    int zero_line_y = -1;
    int zero_line_x = -1;

    if (y_min < 0 && y_max < 0)
        zero_line_y = y;
    else if (y_min > 0 && y_max > 0)
        zero_line_y = 1;
    else
    {
        for (size_t i = 0; i < arr_values_y.size() - 1; i++)
        {
            if (arr_values_y[i] * arr_values_y[i + 1] < 0)
            {
                // при таком х будет линия 0, далее находим ее по у
                zero_line_x = i; 
            }
        }
    }
    float value_y = y_min;
    float closest = 1000000;
    if (zero_line_y == -1)
        for (int i = 0; i < (y - 1); i++)
        {
            float f = fabs(value_y - arr_values_y[zero_line_x]);
            if (f < closest)
            {
                closest = f;
                zero_line_y = i;
            }
            value_y += (y_max - y_min) / (y - 1);
        }
    return y - zero_line_y;
}

int main()
{
    int x, y;
    float x0, x1;
    std::cout << "Write 4 numbers - columns x, rows y, segment [x0, x1]" << std::endl;
    std::cin >> x >> y >> x0 >> x1;

    x++; // +1 под нумерацию
    y++; // +1 под линию 0

    // объявление двумерного динамического массива на y, x элементов
    std::string** arr = new std::string * [y]; 
    for (int c = 0; c < y; c++)
        arr[c] = new std::string[x]; 

    //значения у разбитые на количество х
    std::vector<float> arr_values_y;
    float x_value = x0;
    for (int i = 0; i < (x-1); i++)
    {
        arr_values_y.push_back(func(x_value));
        x_value += (x1 - x0) / (x - 1);
    }

    // находим линию нуля
    int zero_line = find_zero_line(arr_values_y, y);

    //значения у разбитые на количество y
    std::vector<float> arr_values;
    float y_min = *std::min_element(arr_values_y.begin(), arr_values_y.end());
    float y_max = *std::max_element(arr_values_y.begin(), arr_values_y.end());
    float y_value = y_max;
    for (int i = 0; i < y; i++)
    {
        if (i == zero_line)
            arr_values.push_back(0);
        else
        {
            arr_values.push_back(y_value);
            y_value -= (y_max - y_min) / (y - 1);
        }
    }

    // заполнение поля
    int step = 0;
    int k = 1;
    for (int count_row = 0; count_row < y; count_row++) 
    {
        if (k <= 9) 
        {
            arr[count_row][0] = ' ' + std::to_string(k) + ' ';
        }
        else 
        {
            arr[count_row][0] = std::to_string(k) + ' ';
        }
        k += 1;
        for (int count_column = 1; count_column < x; count_column++) 
        {
            if (zero_line == step)
            {
                arr[count_row][count_column] = "-";
            }
            else if (arr_values_y[count_column - 1] <= arr_values[step] && step > zero_line)
                arr[count_row][count_column] = "#";
            else if (arr_values_y[count_column - 1] >= arr_values[step] && step < zero_line)
                arr[count_row][count_column] = "#";
            else
                arr[count_row][count_column] = " ";
        }
        step++;
    }
    
    // вывод массива
    for (int count_row = 0; count_row < y; count_row++)
    {
        std::cout << std::endl;
        for (int count_column = 0; count_column < x; count_column++)
            std::cout << arr[count_row][count_column];
    }
    
    // удаление двумерного динамического массива
    for (int c = 0; c < y; c++)
        delete[]arr[c];

    return 0;
}