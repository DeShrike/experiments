import docx
from docx.enum.style import WD_STYLE_TYPE
from docx.shared import Pt, RGBColor
import os

print(os.getcwd())

doc = docx.Document("test.docx")

for para in doc.paragraphs:
    print(para.text)

    for ix, run in enumerate(para.runs):
        print(f"{ix}\t{run.text}")

para = doc.add_paragraph("This paragraph was added by Python.")
para.add_run("\nThis is line 2.")

cat_para = doc.add_paragraph("This is a ")

run = cat_para.add_run("cat")
run.bold = True
cat_para.add_run(".")

doc.add_picture("cat.jpeg", width = docx.shared.Cm(10))

colcount = 6
rowcount = 4
table = doc.add_table(rows = 1, cols = colcount)
for c in range(colcount):
    table.rows[0].cells[c].text = f"Header {c}"
for r in range(rowcount):
    row = table.add_row().cells
    for c in range(colcount):
        row[c].text = f"{r}-{c}"
# table.style = doc.styles["Light Shading"]

style1 = doc.styles.add_style("MyStyle1", WD_STYLE_TYPE.PARAGRAPH)
style1.base_style = doc.styles["Normal"]
style1.hidden = False
style1.quick_style = True
font = style1.font
font.size = Pt(16)
font.color.rgb = RGBColor(128, 0, 0)

para = doc.add_paragraph("This is a styled paragraph.")
para.style = style1

doc.add_page_break()

#for l in range(10):
#    print(f"Heading {l}")
#    doc.add_heading(f"Heading {l}", l)

for sty in doc.styles:
    print(f"Style: '{sty.name}'")

doc.save("out.docx")

