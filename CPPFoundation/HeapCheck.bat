valgrind --tool=massif --massif-out-file=massif.out --threshold=0.1 --detailed-freq=1 --max-snapshots=1000 ./Program.exe

echo
echo
echo
echo "Use [ms_print massif.out] or if installed [massif-visualizer massif.out] to show HEAP FRAGMENTATION."