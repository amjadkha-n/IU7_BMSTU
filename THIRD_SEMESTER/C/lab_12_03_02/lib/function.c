int add_num_after_even(int *array, int size_array, int*res_array, int size_res_array, int number)
{
    int result_ind = 0;
    int i = 0;
    while (i < size_array)
    {
        if (result_ind < size_res_array)
            res_array[result_ind] = array[i];
        result_ind++;

        if (array[i] % 2 == 0)
        {
            if (result_ind < size_res_array)
                res_array[result_ind] = number;
            result_ind++;
        }
    i++;
    }
    return result_ind;
}