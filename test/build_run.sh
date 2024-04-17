# USAGE:
# Running with no args will build all the tests, run them, and print a summary
# including code coverage:
#
#   ./build_run.sh
#
# If you include the "-report" flag, human readable lcov summaries will be
# generated and dropped in the BUILD_DIR named "<exe name>-html":
#
#   ./build_run.sh -report
#
# If you include the "-clean" flag, the build directory is removed and nothing
# else is done, regardless of other flags.
#
#   ./build_run.sh -clean


# Загрузка и компиляция Google Test
mkdir gtest
cd gtest
git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake ..
make
cd ../../..


# Parse arguments
for opt in "$@"; do
    case $opt in
        -report)
            REPORT=1
            shift  # Next arg
        ;;
        -clean)
            CLEAN=1
            shift  # Next arg
        ;;
    esac
done


BUILD_DIR="_build"

# Output colour codes
NC="\033[0m"          # Normal
CYAN_B="\033[1;36m"   # Bold cyan
RED_B="\033[1;31m"    # Bold red
GREEN_B="\033[1;32m"  # Bold green

# Create array of executable names to store functional results
declare -A EXE
EXE[runSimpleTests]=0

# Create array of executable names to store code coverage results
declare -A COV
COV[runSimpleTests]=0


FAIL=0          # Flag if anything fails
COV_THRESH=100  # Min threshold for code coverage
PREFIX=" >>"    # Prefix for printing status in summary

# Clean case, don't do anything else
if [[ -n $CLEAN ]]; then
    echo -e "${CYAN_B}Cleaning build dir...${NC}"
    rm -rf $BUILD_DIR
    exit
fi

# Create test dir and move there to keep source dir clean
mkdir -p $BUILD_DIR
cd $BUILD_DIR || exit

# Build tests
cmake ..
make || exit

# Run tests
for test in "${!EXE[@]}"; do
    echo -e "\n${CYAN_B}Running $test...${NC}"
    ./$test || EXE[$test]=1
done
