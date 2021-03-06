namespace Properties
{

/// \expose
class PropertyClass
{
public:

  /// \brief Get the pork
  /// \property pork
  float getPork() const;

  /// \brief Set the pork
  /// \property pork
  void setPork(float f);

  /// \brief Set the pie
  /// \property pie
  void setPie(int f);

  /// \brief Set the pork again
  /// \overload
  void setPork(double d);

  /// \brief Get some other instance
  /// \property instance
  PropertyClass &getInstance();

  // \brief 
  void foo();
  // \brief 
  int bar();
};

}