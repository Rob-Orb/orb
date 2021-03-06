#/usr/bin/env bash

_orb_completion()
{
	local cur prev
	COMPREPLY=()
	cur="${COMP_WORDS[COMP_CWORD]}"
	prev="${COMP_WORDS[COMP_CWORD-1]}"

	ORB_RES=''
	ls -1 /etc/bash_completion.d/orb_*_completion.bash > /dev/null 2>&1 
	if [ "$?" == "0" ]; then
		ORB_RES=$(find /etc/bash_completion.d/. -name 'orb_*_completion.bash' -exec basename \{} _completion.bash \; | sed 's/orb_//g' | tr '\r\n' ' ')
	else
		echo ""
		echo "No Orb Applications Installed"
		return 0
	fi
	if [ $COMP_CWORD == 1 ]; then
		COMPREPLY=($(compgen -W "$ORB_RES" -- $cur))
	elif [ $COMP_CWORD == 2 ]; then
		source /etc/bash_completion.d/orb_${prev}_completion.bash
		_orb_${prev}_completion
	fi
	return 0
}

complete -F _orb_completion orb
