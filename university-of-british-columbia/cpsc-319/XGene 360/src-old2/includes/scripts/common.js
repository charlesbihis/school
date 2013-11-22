function TrimStart(strValue)
{
  return strValue.replace(/^\s+/g, '');
}

function TrimEnd(strValue)
{
  return strValue.replace(/\s+$/g, '');
}

function Trim(strValue)
{
  return TrimStart(TrimEnd(strValue));
}
