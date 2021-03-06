# Copyright 2013 David Axmark
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# 	http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

require "#{File.dirname(__FILE__)}/util.rb"
require "#{File.dirname(__FILE__)}/error.rb"
require "#{File.dirname(__FILE__)}/host.rb"

# add functions to this class to allow them to be used as command-line targets
# if no command-line target is chosen, "default" is run.
class Targets
	class Target
		def initialize(name, preqs, &block)
			@name = name
			@preqs = preqs
			@block = block
		end
		
		def invoke
			#puts "preqs of '#{@name}' : #{@preqs}"
			@preqs.each do |p| p.invoke end
			#puts "block of '#{@name}'"
			@block.call if(@block)
		end
	end
	
	@@targets = {}
	@@goals = []
	
	def Targets.reset(args)
		@@targets = {}
		@@args = args
		@@goals = []
	end
	
	def Targets.size() @@targets.size end
	def Targets.goals() @@goals end
	
	def Targets.add(args, &block)
		case args
		when Hash
			fail "Too Many Task Names: #{args.keys.join(' ')}" if args.size > 1
			fail "No Task Name Given" if args.size < 1
			name = args.keys[0]
			preqs = args[name]
			preqs = [preqs] if !preqs.respond_to?(:collect)
			preqs = preqs.collect do |p|
				#puts "testing: #{p.inspect}"
				if(p.respond_to?(:invoke))
					p
				else
					if(@@targets[p] == nil)
						error "Target #{p.inspect} does not exist."
					end
					@@targets[p]
				end
			end
		else
			name = args
			preqs = []
		end
		#puts "Target add '#{name}'"
		@@targets.store(name, Target.new(name, preqs, &block))
	end
	
	# parse ARGV
	def Targets.setup
		return if(@@goals.size != 0)
		if(defined?(@@args) != nil)
			#puts "Got args from reset."
			args = @@args
		else
			#puts "ARGS not defined; going with ARGV."
			args = ARGV
		end
		#puts args.inspect
		args.each do |a| handle_arg(a) end
		if(@@goals.empty?) then
			@@goals = [:default]
		end
		if(!defined?(CONFIG))
			set_const(:CONFIG, 'debug')
		end
		default_const(:RELOAD, false)
		default_const(:USE_NEWLIB, false)
		default_const(:FULLSCREEN, HOST == :linux ? (HOST_PLATFORM == :moblin ? "true" : "false") : "false")
		default_const(:NATIVE_RUNTIME, false)
		default_const(:PROFILING, false)
		default_const(:ELIM, false)
	end
	
	def Targets.handle_arg(a)
		i = a.index('=')
		if(i) then
			name = a[0, i]
			value = a[i+1 .. a.length]
			puts "Set constant #{name.inspect}=#{value.inspect}"
			set_const(name, value)
		else
			@@goals += [a.to_sym]
		end
	end
	
	def Targets.invoke
		setup
		@@goals.each { |t|
			if(@@targets[t] == nil) then
				error "Does not have target '#{t}'"
			end
			@@targets[t].invoke
		}
	end
end

def target(args, &block)
	Targets.add(args, &block)
end
