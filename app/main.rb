require 'sinatra/base'
require 'serialport'
require_relative 'functions'

class MainProgram < Sinatra::Base
   get "/" do
      "the thing"
   end
end