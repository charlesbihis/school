class JugType
{
  public:
    JugType ();
    JugType (int Cap);
    
    int GetContents () const;
    int GetCapacity () const;
    
    void Empty ();
    void Fill ();
  
  private:
    int Capacity, Contents;
};