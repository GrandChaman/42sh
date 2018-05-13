pipeline {
  agent {
    docker {
      image 'briceburg/macos'
    }

  }
  stages {
    stage('Compilation') {
      steps {
        echo 'Begin compile'
        sh 'make'
      }
    }
    stage('Toto') {
      steps {
        sh 'echo Salut'
      }
    }
  }
}