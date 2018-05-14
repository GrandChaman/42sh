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
    stage('Global tests') {
      steps {
        sh './tests_launcher.sh'
      }
    }
  }
  environment {
    TERM = 'xterm-256color'
    PATH = '/bin:/usr/bin'
    SHLVL = '0'
  }
}