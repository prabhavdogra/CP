set -e
g++ -Wl,--stack=268435456 -std=c++17 -DONLINE_JUDGE code.cpp -o code
g++ -Wl,--stack=268435456 -std=c++17 -DONLINE_JUDGE gen.cpp -o gen
g++ -Wl,--stack=268435456 -std=c++17 -DONLINE_JUDGE brute.cpp -o brute
for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./code < input_file > myAnswer
    ./brute < input_file > correctAnswer
    diff -Z myAnswer correctAnswer > /dev/null || break
    echo "Passed test: "  $i
done
echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat myAnswer
echo "Correct answer is:"
cat correctAnswer