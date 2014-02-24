require_relative "Exposer.rb"
require_relative "ExposeAst.rb"
require "json"

# A serialisable class which is exposed in a library.
# Allows querying data of types from other libraries, not parsed in the current operation.
#
class TypeData
  # Create a TypeData, given a short name and a parent, fully qualified path.
  # [parsed] is optional, and should only be supplied if it was parsed in this library.
  def initialize(name, parent, type, parsed=nil)
    @name = name
    @type = type
    @fullyExposed = false
    @parsed = parsed
    @parentClass = parent
  end

  attr_reader :name, :type, :fullyExposed, :parsed, :parentClass

  # Set this class as fully exposed, a fully exposed
  # class can be used as both an input and output argument.
  def setFullyExposed()
    @fullyExposed = true
  end

  # The parent class is supplied on construction, and worked out when creating all
  # class meta data (in the Meta Data Generator). The parent class is the first
  # inherited class which is also exposed.
  def hasParentClass
    return @parentClass != nil
  end

  # Serialise the TypeData to json, except the [@parsed].
  def to_json(opt)
    data = {
      :name => @name,
      :parent => @parentClass
    }
    
    if(@type != :class)
      data[:type] = @type
    end

    if(!@fullyExposed)
      data[:partial] = true
    end
    return JSON.pretty_generate(data, opt)
  end

  # Create a TypeData from json, with a nil [@parsed]
  def self.from_json(data)
    type = :class
    if (data.has_key?(:type))
      type = data[:type]
    end
    cls = TypeData.new(data[:name], data[:parent], type)
    if(!data.include?("partial"))
      cls.setFullyExposed()
    end
    return cls
  end
end

# TypeDataSet is a set of types which are exposed in some library(s).
# The data sets can be restored from disk, and merged to represent multiple libraries types.
class TypeDataSet
  # Create a class set from a hash of fully qualified path, to TypeData
  def initialize(types = {})
    @types = types
    @fullTypes = @types.select { |key, val| val.fullyExposed }
  end

  attr_reader :types, :fullTypes

  # Merge this set with another set.
  def merge(other)
    @types.merge!(other.types)
    @fullTypes.merge!(other.fullTypes)
  end

  # Find the class data for [clsPath] in this set, or nil.
  def findClass(clsPath)
    return types[clsPath]
  end

  # Is the class path passed fully exposed?
  def fullyExposed?(cls)
    return fullTypes.include?(cls)
  end

  # Is the class path passed partially exposed (ie contained at all in the set)?
  def partiallyExposed?(cls)
    return types.include?(cls)
  end

  def fullClassCount
    return fullTypes.length
  end

  # Create a TypeDataSet from two arrays, of fully exposed
  # types, and partially exposed types
  def self.fromClasses(fullClasses, partialClasses, parentClasses, enums)
    types = {}

    # Iterate, find a good parent class, and create the TypeData...
    partialClasses.each do |cls|
      superClass = parentClasses[cls.fullyQualifiedName()]

      types[cls.fullyQualifiedName] = TypeData.new(cls.name, superClass, :class, cls)
    end

    # Now iterate and set any partial types which are full to be full.
    fullClasses.each do |cls|
      obj = types[cls.fullyQualifiedName]
      raise "Classes must also be partial types #{cls.fullyQualifiedName}" unless obj

      obj.setFullyExposed()
    end

    enums.each do |enum|
      type = TypeData.new(enum.name, nil, :enum, enum)
      type.setFullyExposed()
      types[enum.fullyQualifiedName] = type
    end

    return TypeDataSet.new(types)
  end

  # Save this set into [dir], in json form
  def export(dir)
    File.open(dir + "/types.json", 'w') do |file|
      file.write(JSON.pretty_generate(@types))
    end
  end

  # Load a set from [dir].
  def self.import(dir)
    types = JSON.parse(File.open("#{dir}/types.json", "r").read())

    outClasses = {}
    types.each do |ary|
      outClasses[ary[0]] = TypeData.from_json(ary[1])
    end

    return TypeDataSet.new(outClasses)
  end
end