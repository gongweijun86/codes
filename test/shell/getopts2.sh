echo $*
while getopts ":a:bc" opt
do
        case $opt in
                a ) echo $OPTARG
                    echo $OPTIND;;
                b ) echo "b $OPTIND";;
                c ) echo "c $OPTIND";;
                ? ) echo "error"
                    exit 1;;
        esac
done
echo $OPTIND
shift $(($OPTIND - 1))
echo $0
echo $1
echo $*
