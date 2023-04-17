if [ $# -eq 0 ]
	then
		printf "Please provide the name of the class\n"
		printf "Usage: ./$0 [CLASS_NAME]\n"
fi 

cd includes

cat << EOF > $1.hpp
#pragma once

class $1
{
	public:
		$1 &operator=(const $1 &src);
		$1(const $1 &src);
		$1(void);
		~$1(void);
};
EOF

cd ..
cd sources

cat << EOF > $1.cpp
#include <$1.hpp>

$1::$1(void)
{
	//Default $1 Constructor
}

$1::$1(const $1 &src)
{
	//$1 Copy Constructor
}

$1::~$1(void)
{
	//Default $1 Destructor
}

$1 &$1::operator=(const $1 &src)
{
	//$1 Copy Assignment Operator
}
EOF

cd ..
