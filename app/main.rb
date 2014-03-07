require 'sinatra/base'
require_relative 'functions'

class MainProgram < Sinatra::Base
   get "/" do
      "the thing"
   end
end