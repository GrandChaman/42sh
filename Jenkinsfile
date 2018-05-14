pipeline {
  agent {
    node {
      label 'macos'
    }

  }
  stages {
    stage('Compilation') {
      steps {
        sh 'make'
      }
    }
    stage('Toto') {
      steps {
        sh 'echo Salut'
      }
    }
  }
  environment {
    TERM = 'xterm-256color'
    PATH = '/bin:/usr/bin'
    SHLVL = '0'
  }
}