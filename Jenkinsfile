pipeline {
    agent any
    
    stages {
        stage('Checkout') {
            steps {
                git branch: 'main',
                url: 'https://github.com/ArtemCherevatov/Task4.git'
            }
        }
        
        stage('Build') {
            steps {
                bat '''
                    "C:\\Program Files\\Microsoft Visual Studio\\2022\\Professional\\MSBuild\\Current\\Bin\\MSBuild.exe" test_repos.sln ^
                    /p:Configuration=Debug ^
                    /p:Platform=x64 ^
                    /p:WindowsTargetPlatformVersion=10.0.19041.0
                '''
            }
        }
        
        stage('Test') {
            steps {
                bat '''
                    cd x64\\Debug
                    test_repos.exe --gtest_output="xml:test_report.xml"
                '''
                junit 'x64/Debug/test_report.xml'
            }
        }
    }
    
    post {
        always {
            echo 'Build completed'
        }
        success {
            echo 'Build and tests completed successfully!'
        }
        failure {
            echo 'Build or tests failed!'
        }
    }
}
