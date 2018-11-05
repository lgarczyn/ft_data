#!/bin/sh

if [ -z "$1" ] ; then
	echo "need file name"
	exit 1
fi

if [ -f "xx*" ] ; then
	gio trash xx*
fi

generate_prototype()
{
	echo "/*\n** $name\n*/" >> "$dirname/${dirname}_int.h"
	cat $dirname/$name |
		perl -0777ne '
		while (/(\n)((const )?[a-z_]+)(\t+)([\*a-z_]+\([^\n]*?)(\n?\t?)([^\n]*?)(\))/sg)
		{
			if ($6 eq "")
			{
				print "$2|$5$7$8;\n"
			}
			else
			{
				print "$2|$5 $7$8;\n"
			}
		}' |
		column -ts '|' |
		unexpand -at 4 |
		sed -r 's/\ +/\t/' >> "$dirname/${dirname}_int.h"

	# awk '/^((const )?[a-z_]+)(\t+)(\*?)([a-z_]+)\(/,/)/' $1

	# ctags -x --c-kinds=fp pma.c |
	# 	awk '{
	# 		s = $5 "|"; 
	# 		for (i = 6; i <= NF; i++)
	# 			s = s $i " ";
	# 		print s
	# 	}' |
	# 	column -ts '|' |
	# 	unexpand -at 4 |
	# 	sed -r 's/\ +/\t/' > "$dirname/${dirname}_int.h"
}

dirname=${1%\.*}
mkdir -p $dirname

csplit -s $1 /^//.*\.c$/ "{*}"

mv xx00 header.tmp

i=1

cat header.tmp > "$dirname/${dirname}_int.h"

uppercase=`echo ${dirname} | tr [a-z] [A-Z]`
echo "\n#ifndef _${uppercase}_INT_H" >> "$dirname/${dirname}_int.h"
echo "# define _${uppercase}_INT_H\n" >> "$dirname/${dirname}_int.h"
echo "" >> "$dirname/${dirname}_int.h"

for file in xx*
do
	name=`grep -P "^//.+\.c" $file | cut -c3-`
	if [ -z "$name" ] ; then
		name=$1
	fi
	

	cat header.tmp > "$dirname/$name"
	echo "#include \"${dirname}_int.h\"" >> "$dirname/$name"
	cat $file | tail -n +2 >> "$dirname/$name"

	generate_prototype	

done

echo "#endif" >> "$dirname/${dirname}_int.h"

rm header.tmp xx*
