#/usr/bin/env bash
_orb_upload_completion()
{
	local cur prev

	#COMPREPLY=()
	cur="${COMP_WORDS[COMP_CWORD]}"
	prev="${COMP_WORDS[COMP_CWORD-1]}"

	RESULT="$(wget -qO - https://rob-orb.github.io/firmwares/ls.index | tr '\r\n' ' ')"
	
	if [ $COMP_CWORD == 2 ]; then
		case "$prev" in
			"upload")
			COMPREPLY=($(compgen -W "$RESULT" -- $cur));;
		*)
		;;
		esac
	fi
	return 0
}
#complete -F _orb_upload_completion orb
