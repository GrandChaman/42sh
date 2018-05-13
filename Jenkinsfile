pipeline {
  agent none
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