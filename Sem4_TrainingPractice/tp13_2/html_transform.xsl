<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/company">
		<xsl:param name="counter" select="0"/>
		<html> 
			<body>
				<h2>Company info</h2>
				<table border="1">
					<tr style="background-color: blue">
						<th style="text-align:left">Full Name</th>
						<th style="text-align:left">Age</th>
						<th style="text-align:left">Sex</th>
						<th style="text-align:left">Unfireable</th>
						<th style="text-align:left">Position</th>
						<th style="text-align:left">Employment Form</th>
						<th style="text-align:left">Salary</th>
					</tr>
					<xsl:apply-templates/>
				</table>
			</body>
		</html>
	</xsl:template>
	<xsl:template match="employee">
		<tr>
			<td>
				<xsl:value-of select="text()"/>
			</td>
			<td>
				<xsl:value-of select="@age"/>
			</td>
			<td>
				<xsl:value-of select="@sex"/>
			</td>
			<td>
				<xsl:value-of select="@unfireable"/>
			</td>
			<td>
				<xsl:value-of select="position"/>
			</td>
			<td>
				<xsl:value-of select="employmentForm"/>
			</td>
			<td>
				<xsl:value-of select="salary"/>$
			</td>
		</tr>
		<xsl:apply-templates select="subordinates"/>
	</xsl:template>
</xsl:stylesheet>
