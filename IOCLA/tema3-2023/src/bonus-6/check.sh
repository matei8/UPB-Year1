#!/bin/bash
TASK_SCORE=5
TOTAL=0
ZERO_FOUND=0
NONZERO_FOUND=0

echo "===================== Timegate ====================="

HAS_RDRAND="true"
if [ -z $(grep -o rdrand /proc/cpuinfo | uniq) ]; then
	echo "WARNING: the machine doesn't support RDRAND"
	HAS_RDRAND="false"
fi

for i in 1 2 3 4 5; do
	if [ $HAS_RDRAND == "true" ]; then
		OUTPUT=$(./checker)
	else
		echo "Emulating RDRAND"
		OUTPUT=$(qemu-i386 -cpu IvyBridge,+rdrand ./checker 2> /dev/null)
	fi
	if [ $OUTPUT == "0" ]; then
		ZERO_FOUND="1"
		break
	fi
done
for i in 1 2 3 4 5; do
	if [ $HAS_RDRAND == "true" ]; then
		OUTPUT=$(gdb ./checker -x gdb_commands | tail -n 2 | head -n 1)
		if [ $OUTPUT != "0" ]; then
			NONZERO_FOUND="1"
			break
		fi
	else
		echo "Can't test second part of the task; manual check required"
		break
	fi
done
if [ $ZERO_FOUND == "1" ]; then
	echo "Error: You didn't generate a random number, but you should have"
fi
if [ $NONZERO_FOUND == "1" ]; then
	echo "Error: You generated a random number, but you shouldn't have"
fi
if [ $ZERO_FOUND == "0" ] && [ $NONZERO_FOUND == "0" ]; then
	TOTAL=$TASK_SCORE
fi

echo
printf "BONUS 6 SCORE: %3.2f / %3.2f\n" ${TOTAL} ${TASK_SCORE}
