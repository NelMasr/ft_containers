mkdir outs

echo "Generating out files for vector"
./ft_vector > outs/out_ft_vector
./std_vector > outs/out_std_vector

echo "Generating out files for map"
./ft_map > outs/out_ft_map
./std_map > outs/out_std_map

echo "Generating out files for stack"
./ft_stack > outs/out_ft_stack
./std_stack > outs/out_std_stack

echo "\n===================================================\n"

echo "calling diff on vector ft and std files"
diff outs/out_ft_vector outs/out_std_vector

if [ $? -eq 0 ]
then
    echo "\033[0;32mOK.\033[0m\n"
else
    echo "\033[0;31mCapacity differs: no standard for capacity. See ISO file.\033[0m\n"
fi

echo "calling diff on map ft and std files"
diff outs/out_ft_map outs/out_std_map

if [ $? -eq 0 ]
then
    echo "\033[0;32mOK.\033[0m\n"
else
    echo "\033[0;31mERROR.\033[0m\n"
fi

echo "calling diff on stack ft and std files"
diff outs/out_ft_stack outs/out_std_stack

if [ $? -eq 0 ]
then
    echo "\033[0;32mOK.\033[0m\n"
else
    echo "\033[0;31mERROR.\033[0m\n"
fi
