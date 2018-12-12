#/usr/bin/env bash
_orb_analog_completion()
{
	local cur prev

	#COMPREPLY=()
	cur="${COMP_WORDS[COMP_CWORD]}"
	prev="${COMP_WORDS[COMP_CWORD-1]}"

	if [ $COMP_CWORD == 2 ]; then
		case "$prev" in
			"analog")
			COMPREPLY=($(compgen -W "-r -a" -- $cur));;
		*)
		;;
		esac
	fi
	return 0
}
