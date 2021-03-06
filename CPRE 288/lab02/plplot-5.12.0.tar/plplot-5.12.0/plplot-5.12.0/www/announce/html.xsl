<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'
                xmlns="http://www.w3.org/TR/xhtml1/transitional"
                exclude-result-prefixes="#default">
					
<xsl:import
  href="/usr/share/sgml/docbook/stylesheet/xsl/nwalsh/xhtml/docbook.xsl"/>

<xsl:param name="html.stylesheet" select="'announce.css'"/>

<xsl:param name="shade.verbatim" select="1"/>
<xsl:attribute-set name="shade.verbatim.style">
  <xsl:attribute name="border">1</xsl:attribute>
  <xsl:attribute name="bgcolor">#E0FFE0</xsl:attribute>
</xsl:attribute-set>

</xsl:stylesheet>
