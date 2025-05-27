import os
import argparse

def process_directory(directory_path, output_file, root_path=None, current_depth=1):
    """
    递归处理目录，将 C++ 文件内容写入 Markdown 文件
    :param directory_path: 当前处理的目录路径
    :param output_file: 输出的Markdown文件对象
    :param root_path: 根目录路径（用于计算相对路径）
    :param current_depth: 当前目录深度（用于确定标题级别）
    """
    if root_path is None:
        root_path = directory_path
    
    # 获取当前目录相对于根目录的路径
    rel_path = os.path.relpath(directory_path, root_path)
    
    # 如果不是根目录，添加目录标题
    if rel_path != '.':
        # 写入目录标题（H1, H2, H3... 根据深度决定）
        dir_name = os.path.basename(directory_path)
        heading = '#' * current_depth
        output_file.write(f"{heading} {dir_name}\n\n")
    
    # 处理当前目录下的所有文件（按字典序排序）
    for item in sorted(os.listdir(directory_path), key=lambda x: x.lower()):
        item_path = os.path.join(directory_path, item)
        
        # 如果是文件且是C++文件
        if os.path.isfile(item_path) and item.lower().endswith(('.cpp', '.h', '.hpp', '.cxx', '.cc')):
            # 写入文件名
            output_file.write(f"**{item}**\n\n```cpp\n")
            
            # 写入文件内容
            try:
                with open(item_path, 'r', encoding='utf-8') as f:
                    content = f.read()
                    output_file.write(content)
                    if not content.endswith('\n'):
                        output_file.write('\n')
            except UnicodeDecodeError:
                try:
                    with open(item_path, 'r', encoding='gbk') as f:
                        content = f.read()
                        output_file.write(content)
                        if not content.endswith('\n'):
                            output_file.write('\n')
                except Exception as e:
                    output_file.write(f"\n// Error reading file: {str(e)}\n")
            except Exception as e:
                output_file.write(f"\n// Error reading file: {str(e)}\n")
            
            output_file.write("```\n\n")
    
    # 递归处理子目录（按字典序排序）
    for item in sorted(os.listdir(directory_path), key=lambda x: x.lower()):
        item_path = os.path.join(directory_path, item)
        if os.path.isdir(item_path):
            process_directory(item_path, output_file, root_path, current_depth + 1)

def main():
    parser = argparse.ArgumentParser(description='Aggregate C++ files into a single Markdown document with hierarchical headings.')
    parser.add_argument('directory', help='Directory containing C++ files')
    parser.add_argument('output', help='Output Markdown file path')
    
    args = parser.parse_args()
    
    with open(args.output, 'w', encoding='utf-8') as md_file:
        process_directory(args.directory, md_file)
    
    print(f"Markdown file generated at: {args.output}")

if __name__ == "__main__":
    main()