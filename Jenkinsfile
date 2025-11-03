pipeline {
    agent any
    tools {
        msbuild 'MSBuild_Default'
    }
    stages {
        stage('Checkout') {
            steps {
                git branch: 'main',
                url: 'https://github.com/ArtemCherevatov/Task4.git',
                credentialsId: 'github-access'
            }
        }
        stage('Build') {
            steps {
                bat 'msbuild test_repos.sln /p:Configuration=Debug /p:Platform=x64 /p:WindowsTargetPlatformVersion=10.0.19041.0'
            }
        }
        stage('Test') {
            steps {
                bat 'cd x64\\Debug && test_repos.exe --gtest_output=\"xml:test_report.xml\"'
            }
        }
    }
    post {
        always {
            // Додаємо дії в секцію always
            echo 'Build completed - checking test results'
            xunit (
                [GoogleTest(
                    pattern: 'x64/Debug/test_report.xml',
                    skipIfNoTestFiles: true
                )]
            )
        }
        success {
            echo 'Build and tests completed successfully!'
        }
        failure {
            echo 'Build or tests failed!'
        }
    }
}
