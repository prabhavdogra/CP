PEDANTIC_FLAGS=" -O2 -std=c++17 -Wl,--stack=268435456 -g -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fstack-protector "

PROBLEMATIC_FLAGS_FIX=" -Wno-unused-parameter -Wno-unused-variable -Wno-variadic-macros -Wno-conversion "

NORMAL_FLAGS=" -O2 -std=c++17 -Wl,--stack=268435456 -ftree-vectorize -fopt-info-vec -Wshadow "

LOCAL_FLAGS=" -Dprabhav_ -DDEBUG "

FILE=$1
FILE_CPP=$FILE".cpp"
FILE_EXE=$FILE".exe"
if test -f "$FILE"; then
    rm $FILE
fi

DEBUG_=${2:-"0"}
FLAGS=$LOCAL_FLAGS

if [ "$DEBUG_" = "D" ]; then
	FLAGS+=$PEDANTIC_FLAGS
    FLAGS+=$PROBLEMATIC_FLAGS_FIX
else
	FLAGS+=$NORMAL_FLAGS
fi

COMMAND="g++ $FLAGS $FILE_CPP -o $FILE"
echo $COMMAND
OUTPUT=$($COMMAND)

echo $OUTPUT

if test -f "$FILE"; then
    ./$FILE_EXE
fi
