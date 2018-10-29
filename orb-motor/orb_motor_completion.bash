#/usr/bin/env bash
_orb_motor_completion()
{
	local cur prev

	#COMPREPLY=()
	cur="${COMP_WORDS[COMP_CWORD]}"
	prev="${COMP_WORDS[COMP_CWORD-1]}"

	if [ $COMP_CWORD == 2 ]; then
		case "$prev" in
			"motor")
			COMPREPLY=($(compgen -W "-d -m -r" -- $cur));;
		*)
		;;
		esac
	fi
	return 0
}
