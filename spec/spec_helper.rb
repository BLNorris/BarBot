ENV['RACK_ENV'] = 'test'

require_relative '../app/main'


#setup Capybara to point to our main class
require 'capybara/rspec'
Capybara.app = MainProgram