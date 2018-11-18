echo 'y\n\n\n' | valgrind --tool=callgrind ./ft_data && kcachegrind `ls -t callgrind.out.* | head -1`
