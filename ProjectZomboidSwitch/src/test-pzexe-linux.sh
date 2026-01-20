#!/bin/bash

# Use this to run ProjectZomboid32/64 launcher from workdir

INSTDIR=../Build/Client/Linux/projectzomboid

if "${INSTDIR}/jre64/bin/java" -version > /dev/null 2>&1; then
	echo "64-bit java detected"
	export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:../natives/linux64:../natives"
	JSIG="${INSTDIR}/jre64/lib/libjsig.so"
	# XMODIFIERS is cleared here to prevent SCIM screwing up keyboard input
	XMODIFIERS= LD_PRELOAD=$LD_PRELOAD:$JSIG \
		${INSTDIR}/ProjectZomboid64 \
		-pzexejavacmd "${INSTDIR}/jre64/bin/java -classpath ../lib/pzexe.jar zombie.pzexe" \
		-pzexeconfig test-pzexe-linux-64.json \
		"$@"
elif "${INSTDIR}/jre/bin/java" -client -version > /dev/null 2>&1; then
	echo "32-bit java detected"
	export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:../natives/linux32:../natives"
	JSIG="${INSTDIR}/jre/lib/libjsig.so"
	# XMODIFIERS is cleared here to prevent SCIM screwing up keyboard input
	XMODIFIERS= LD_PRELOAD=$LD_PRELOAD:$JSIG \
		${INSTDIR}/ProjectZomboid32 \
		-pzexejavacmd "${INSTDIR}/jre/bin/java -classpath ../lib/pzexe.jar zombie.pzexe" \
		-pzexeconfig test-pzexe-linux-32.json \
		"$@"
else
	echo "couldn't determine 32/64 bit of java"
fi
exit 0

