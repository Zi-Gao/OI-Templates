#!/usr/bin/env python3
"""
将目录中的CPP文件转换为带语法高亮的LaTeX文档
Usage: python main.py -d <input_dir> -o <output_dir>
"""

import os
import click
from pathlib import Path


def escape_latex(text: str) -> str:
    replacements = [
        ('\\', r'\textbackslash{}'),
        ('&', r'\&'),
        ('%', r'\%'),
        ('$', r'\$'),
        ('#', r'\#'),
        ('^', r'\^{}'),
        ('_', r'\_'),
        ('{', r'\{'),
        ('}', r'\}'),
        ('~', r'\~{}'),
    ]
    for old, new in replacements:
        text = text.replace(old, new)
    return text


def collect_cpp_files(input_dir: Path) -> dict:
    chapters = {}
    for item in sorted(input_dir.rglob('*.cpp')):
        rel_path = item.relative_to(input_dir)
        parts = rel_path.parts
        chapter = '__root__' if len(parts) == 1 else parts[0]
        chapters.setdefault(chapter, []).append((rel_path, item))
    for chapter in chapters:
        chapters[chapter].sort(key=lambda x: str(x[0]))
    return chapters


def file_to_subdir(rel_path: Path) -> tuple[str, str]:
    parts = rel_path.parts
    if len(parts) <= 2:
        return ('', parts[-1])
    return (str(Path(*parts[1:-1])), parts[-1])


def generate_latex_header() -> list[str]:
    lines = []

    lines.append(r'\documentclass[a4paper,11pt]{article}')
    lines.append('')

    # ------------------------------------------------------------------ 字体
    lines.append(r'% ===== 字体（XeLaTeX） =====')
    lines.append(r'\usepackage{fontspec}')
    lines.append(r'\usepackage{xeCJK}')
    lines.append(r'\setmainfont{JetBrains Mono}[Scale=0.85]')
    lines.append(r'\setsansfont{JetBrains Mono}[Scale=0.85]')
    lines.append(r'\setmonofont{JetBrains Mono}[Scale=0.85]')
    lines.append(r'\setCJKmainfont{PingFang SC}')
    lines.append(r'\setCJKsansfont{PingFang SC}')
    lines.append(r'\setCJKmonofont{PingFang SC}')
    lines.append('')

    # ------------------------------------------------------------------ 页面
    lines.append(r'% ===== 页面设置 =====')
    lines.append(r'\usepackage[')
    lines.append(r'    a4paper,')
    lines.append(r'    top=2.5cm,')
    lines.append(r'    bottom=2.5cm,')
    lines.append(r'    left=2.5cm,')
    lines.append(r'    right=2.5cm')
    lines.append(r']{geometry}')
    lines.append('')

    # ------------------------------------------------------------------ 页眉页脚
    lines.append(r'% ===== 页眉页脚 =====')
    lines.append(r'\usepackage{fancyhdr}')
    lines.append(r'\pagestyle{fancy}')
    lines.append(r'\fancyhf{}')
    lines.append(r'\fancyfoot[C]{\thepage}')
    lines.append(r'\renewcommand{\headrulewidth}{0pt}')
    lines.append(r'\renewcommand{\footrulewidth}{0pt}')
    lines.append(r'\fancypagestyle{plain}{\fancyhf{}\fancyfoot[C]{\thepage}'
                 r'\renewcommand{\headrulewidth}{0pt}}')
    lines.append('')

    # ------------------------------------------------------------------ 超链接
    lines.append(r'% ===== 超链接 =====')
    lines.append(r'\usepackage{hyperref}')
    lines.append(r'\hypersetup{')
    lines.append(r'    colorlinks=true,')
    lines.append(r'    linkcolor=black,')
    lines.append(r'    pdfborder={0 0 0}')
    lines.append(r'}')
    lines.append('')

    # ------------------------------------------------------------------ 目录间距
    lines.append(r'% ===== 目录编号宽度 =====')
    lines.append(r'\usepackage{tocloft}')
    lines.append(r'\setlength{\cftsecnumwidth}{2.5em}')
    lines.append(r'\setlength{\cftsecindent}{0em}')
    lines.append(r'\setlength{\cftsubsecnumwidth}{3.2em}')
    lines.append(r'\setlength{\cftsubsecindent}{2.5em}')
    lines.append(r'\setlength{\cftsubsubsecnumwidth}{3.8em}')
    lines.append(r'\setlength{\cftsubsubsecindent}{5.7em}')
    lines.append('')

    # ------------------------------------------------------------------ 颜色
    lines.append(r'% ===== 颜色 =====')
    lines.append(r'\usepackage{xcolor}')
    lines.append(r'\definecolor{framecolor}{gray}{0.55}')
    lines.append(r'\definecolor{rowlinecolor}{gray}{0.88}')
    lines.append(r'\definecolor{linenumcolor}{gray}{0.50}')
    lines.append('')

    # ------------------------------------------------------------------ minted
    # 关键：finalizecache 在首次生成缓存后改用 frozencache 可完全规避
    # 但最简单稳定的方法是禁用缓存（cache=false），避免路径/权限问题
    lines.append(r'% ===== minted（禁用缓存，避免 .data.minted 路径错误） =====')
    lines.append(r'\usepackage[cache=false]{minted}')
    lines.append(r'\renewcommand{\theFancyVerbLine}{%')
    lines.append(r'    \textcolor{linenumcolor}{\normalsize\arabic{FancyVerbLine}}%')
    lines.append(r'}')
    lines.append(r'\setminted{')
    lines.append(r'    style=xcode,')
    lines.append(r'    bgcolor=white,')
    lines.append(r'    linenos=true,')
    lines.append(r'    numbersep=10pt,')
    lines.append(r'    fontsize=\normalsize,')
    lines.append(r'    breaklines=true,')
    lines.append(r'    breakanywhere=true,')
    lines.append(r'    tabsize=4,')
    lines.append(r'    baselinestretch=1.2,')
    lines.append(r'}')
    lines.append('')

    # ------------------------------------------------------------------ tcolorbox
    lines.append(r'% ===== tcolorbox =====')
    lines.append(r'\usepackage{tcolorbox}')
    lines.append(r'\tcbuselibrary{minted,skins,breakable}')
    lines.append('')
    lines.append(r'\tcbset{')
    lines.append(r'    codestyle/.style={')
    lines.append(r'        enhanced jigsaw,')
    lines.append(r'        breakable,')
    lines.append(r'        colback=white,')
    lines.append(r'        colframe=framecolor,')
    lines.append(r'        boxrule=0.6pt,')
    lines.append(r'        arc=2pt,')
    lines.append(r'        left=0pt, right=0pt,')
    lines.append(r'        top=2pt, bottom=2pt,')
    lines.append(r'        watermark tikz={')
    lines.append(r'            \foreach \y in {1,...,100}{')
    lines.append(r'                \draw[rowlinecolor, line width=0.3pt]')
    lines.append(r'                    (0, {-\y * \baselineskip * 1.2 + 0.3ex})')
    lines.append(r'                    -- (\linewidth,')
    lines.append(r'                       {-\y * \baselineskip * 1.2 + 0.3ex});')
    lines.append(r'            }')
    lines.append(r'        },')
    lines.append(r'    }')
    lines.append(r'}')
    lines.append('')

    # ------------------------------------------------------------------ 章节
    lines.append(r'% ===== 章节标题 =====')
    lines.append(r'\usepackage{titlesec}')
    lines.append(r'\titleformat{\section}{\Large\bfseries}{}{0em}{}[\titlerule]')
    lines.append(r'\titlespacing{\section}{0pt}{1.5em}{0.8em}')
    lines.append(r'\titleformat{\subsection}{\large\bfseries}{}{0em}{}'
                 r'[\vspace{0.2em}\hrule height 0.4pt]')
    lines.append(r'\titlespacing{\subsection}{0pt}{1.2em}{0.5em}')
    lines.append(r'\titleformat{\subsubsection}{\normalsize\bfseries}{}{0em}{}')
    lines.append(r'\titlespacing{\subsubsection}{0pt}{0.8em}{0.3em}')
    lines.append('')

    lines.append(r'\usepackage{parskip}')
    lines.append(r'\setlength{\parskip}{0pt}')
    lines.append('')

    return lines


def _append_codeblock(lines: list, abs_path: Path) -> None:
    safe_path = str(abs_path).replace('\\', '/')
    lines.append(r'\begin{tcolorbox}[codestyle]')
    lines.append(r'\inputminted{cpp}{' + safe_path + r'}')
    lines.append(r'\end{tcolorbox}')


def generate_latex(input_dir: Path, chapters: dict) -> str:
    lines = generate_latex_header()

    lines.append(r'\begin{document}')
    lines.append('')

    lines.append(r'\pagenumbering{roman}')
    lines.append(r'\tableofcontents')
    lines.append(r'\clearpage')
    lines.append(r'\pagenumbering{arabic}')
    lines.append('')

    # ---------- 根目录文件 ----------
    if '__root__' in chapters:
        for rel_path, abs_path in chapters['__root__']:
            display_name = escape_latex(str(rel_path))
            file_label = 'file:' + str(rel_path).replace('/', ':').replace('.', '-')
            lines.append(r'\subsection*{' + display_name + r'}')
            lines.append(r'\addcontentsline{toc}{subsection}{' + display_name + r'}')
            lines.append(r'\label{' + file_label + r'}')
            _append_codeblock(lines, abs_path)
            lines.append(r'\clearpage')
            lines.append('')

    # ---------- 各 chapter ----------
    sorted_chapters = sorted(
        [(k, v) for k, v in chapters.items() if k != '__root__'],
        key=lambda x: x[0]
    )

    for chapter_name, files in sorted_chapters:
        escaped_chapter = escape_latex(chapter_name)
        chapter_label = 'ch:' + chapter_name.replace(' ', '-')

        lines.append(r'\section{' + escaped_chapter + r'}')
        lines.append(r'\label{' + chapter_label + r'}')
        lines.append('')

        subdir_groups: dict[str, list] = {}
        for rel_path, abs_path in files:
            subdir_key, _ = file_to_subdir(rel_path)
            subdir_groups.setdefault(subdir_key, []).append((rel_path, abs_path))

        for subdir_key in sorted(subdir_groups.keys()):
            group_files = subdir_groups[subdir_key]

            if subdir_key:
                escaped_subdir = escape_latex(subdir_key)
                subdir_label = ('subdir:' + chapter_name + ':' +
                                subdir_key.replace('/', ':').replace(' ', '-'))
                lines.append(r'\subsection{' + escaped_subdir + r'}')
                lines.append(r'\label{' + subdir_label + r'}')
                lines.append('')

                for rel_path, abs_path in group_files:
                    _, filename = file_to_subdir(rel_path)
                    file_label = ('file:' +
                                  str(rel_path).replace('/', ':').replace('.', '-'))
                    lines.append(r'\subsubsection{' + escape_latex(filename) + r'}')
                    lines.append(r'\label{' + file_label + r'}')
                    _append_codeblock(lines, abs_path)
                    lines.append(r'\clearpage')
                    lines.append('')
            else:
                for rel_path, abs_path in group_files:
                    _, filename = file_to_subdir(rel_path)
                    file_label = ('file:' +
                                  str(rel_path).replace('/', ':').replace('.', '-'))
                    lines.append(r'\subsection{' + escape_latex(filename) + r'}')
                    lines.append(r'\label{' + file_label + r'}')
                    _append_codeblock(lines, abs_path)
                    lines.append(r'\clearpage')
                    lines.append('')

    lines.append(r'\end{document}')
    return '\n'.join(lines)


def generate_build_script(tex_filename: str) -> str:
    stem = Path(tex_filename).stem
    return f'''#!/bin/bash
# 编译 LaTeX 文档
# 每次编译前清理 .aux 防止损坏的辅助文件导致扫描错误

set -e

SCRIPT_DIR="$(cd "$(dirname "${{BASH_SOURCE[0]}}")" && pwd)"
cd "$SCRIPT_DIR"

TEX="{tex_filename}"
NAME="{stem}"

# 清理可能损坏的旧辅助文件
clean_aux() {{
    rm -f "$NAME".aux "$NAME".toc "$NAME".out \
          "$NAME".log "$NAME".fls "$NAME".fdb_latexmk \
          "$NAME".pyg
    # minted v3 缓存目录
    rm -rf "_minted-$NAME" "_minted"
    # minted v3 新式 .data/.errlog 文件
    rm -f *.data.minted *.errlog.minted
}}

echo "==> 清理旧辅助文件..."
clean_aux

echo "==> 第一次编译..."
xelatex -shell-escape -interaction=nonstopmode "$TEX" || true

echo "==> 第二次编译（写入 .toc）..."
xelatex -shell-escape -interaction=nonstopmode "$TEX" || true

echo "==> 第三次编译（目录页码最终对齐）..."
xelatex -shell-escape -interaction=nonstopmode "$TEX"

echo "==> 清理辅助文件..."
clean_aux

echo "==> 完成：$NAME.pdf"
'''


@click.command()
@click.option('-d', 'input_dir', required=True,
              type=click.Path(exists=True, file_okay=False, dir_okay=True),
              help='输入目录（含cpp文件）')
@click.option('-o', 'output_dir', required=True,
              type=click.Path(file_okay=False, dir_okay=True),
              help='输出目录（存放tex和sh）')
@click.option('--name', default='code', show_default=True,
              help='输出文件名（不含扩展名）')
def main(input_dir: str, output_dir: str, name: str):
    input_path = Path(input_dir).resolve()
    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)
    output_path = output_path.resolve()

    click.echo(f'输入目录: {input_path}')
    click.echo(f'输出目录: {output_path}')

    chapters = collect_cpp_files(input_path)
    if not chapters:
        click.echo('警告：未找到任何 .cpp 文件', err=True)
        return

    total = sum(len(v) for v in chapters.values())
    click.echo(f'找到 {total} 个cpp文件，{len(chapters)} 个章节')

    tex_filename = f'{name}.tex'
    tex_path = output_path / tex_filename
    tex_path.write_text(generate_latex(input_path, chapters), encoding='utf-8')
    click.echo(f'已生成: {tex_path}')

    sh_filename = f'build_{name}.sh'
    sh_path = output_path / sh_filename
    sh_path.write_text(generate_build_script(tex_filename), encoding='utf-8')
    os.chmod(sh_path, 0o755)
    click.echo(f'已生成: {sh_path}')

    click.echo(f'\n编译方法:\n  cd {output_path}\n  ./{sh_filename}')


if __name__ == '__main__':
    main()