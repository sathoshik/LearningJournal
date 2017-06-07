#!/bin/bash

git_env() {
  pushd $SSH_HOME > /dev/null 

  line=$(head -n 1 ~/.ssh/.rsa_config)
  
  if [ -z $@ ]; then
    echo "$(tput setaf 3)Current git enviornment is $line.$(tput sgr 0)"
  elif [ $line != $@ ]; then
    case "$@" in
      earnwithdrop)
        echo $@ > .rsa_config
        mv id_rsa.pub id_rsa_sathoshi.pub
        mv id_rsa id_rsa_sathoshi

        mv id_rsa_earnwithdrop.pub id_rsa.pub
        mv id_rsa_earnwithdrop id_rsa
        echo "$(tput setaf 2)Successfully changed git enviornment to earnwithdrop$(tput sgr 0)"
        ;;
      sathoshi)
        echo $@ > .rsa_config
        mv id_rsa.pub id_rsa_earnwithdrop.pub
        mv id_rsa id_rsa_earnwithdrop

        mv id_rsa_sathoshi.pub id_rsa.pub
        mv id_rsa_sathoshi id_rsa
        echo "$(tput setaf 2)Successfully changed git enviornment to sathoshi$(tput sgr 0)"
        ;;
      *)
        echo "$(tput setaf 1)Fatal Error. No git enviornment configured as $@.$(tput sgr 0)"
    esac
  else
    echo "$(tput setaf 1)Fatal Error. Current git enviornment is already $line.$(tput sgr 0)"
  fi

  popd > /dev/null
}
