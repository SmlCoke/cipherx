import re
import argparse
from pathlib import Path
from typing import List, Tuple

class MarkdownTOCGenerator:
    """Markdown 目录自动生成器"""
    
    def __init__(self, markdown_file: str):
        """
        初始化生成器
        
        Args:
            markdown_file: Markdown 文件路径
        """
        self.file_path = Path(markdown_file)
        self.content = self.file_path.read_text(encoding='utf-8')
        self.headings = self._extract_headings()
    
    def _extract_headings(self) -> List[Tuple[int, str]]:
        """
        提取所有标题及其分级
        
        Returns:
            列表，每个元素为 (分级数, 标题文本)
        """
        # 匹配 Markdown 标题：^#+\s+(.+)$
        pattern = r'^(#+)\s+(.+)$'
        headings = []
        
        for line in self.content.split('\n'):
            match = re.match(pattern, line)
            if match:
                level = len(match.group(1))  # "#" 的个数
                title = match.group(2).strip()
                headings.append((level, title))
        
        return headings
    
    def _generate_anchor(self, title: str) -> str:
        """
        根据标题生成锚点链接
        
        GitHub/GitLab Markdown 规则:
        - 转为小写
        - 空格替换为 "-"
        - 移除特殊字符
        - 只保留字母、数字、"-"、中文
        
        Args:
            title: 标题文本
            
        Returns:
            锚点链接
        """
        # 转为小写
        anchor = title.lower()
        # 替换空格为 "-"
        anchor = re.sub(r'\s+', '-', anchor)
        # 移除不支持的特殊字符（保留中文、字母、数字、"-"）
        anchor = re.sub(r'[^a-z0-9\u4e00-\u9fff\-]', '', anchor)
        # 移除多个连续的 "-"
        anchor = re.sub(r'-+', '-', anchor)
        # 移除开头和结尾的 "-"
        anchor = anchor.strip('-')
        
        return anchor
    
    def _generate_toc(self) -> str:
        """
        生成目录文本
        
        Returns:
            目录的 Markdown 文本
        """
        if not self.headings:
            return ""
        
        toc_lines = ["# 目录\n"]
        
        for level, title in self.headings:
            # 跳过第一级标题（通常作为文档标题）
            if level == 1:
                continue
            
            # 计算缩进（每级缩进 2 个空格）
            indent = "  " * (level - 2)
            anchor = self._generate_anchor(title)
            
            # 生成目录项：- [标题](# 锚点)
            toc_line = f"{indent}- [{title}](#{anchor})"
            toc_lines.append(toc_line)
        
        return "\n".join(toc_lines)
    
    def insert_toc(self, insert_after_line: int = 0) -> str:
        """
        将目录插入到文档中
        
        Args:
            insert_after_line: 在第几行后插入目录（0 表示最开始）
            
        Returns:
            插入目录后的完整内容
        """
        toc = self._generate_toc()
        lines = self.content.split('\n')
        
        # 在指定位置插入目录
        lines.insert(insert_after_line, toc)
        
        return '\n'.join(lines)
    
    def save_with_toc(self, output_file: str = None, insert_after_line: int = 0):
        """
        生成带目录的新文件
        
        Args:
            output_file: 输出文件路径（默认覆盖原文件）
            insert_after_line: 在第几行后插入目录
        """
        if output_file is None:
            output_file = self.file_path
        
        new_content = self.insert_toc(insert_after_line)
        Path(output_file).write_text(new_content, encoding='utf-8')
        print(f"✓ 已保存到: {output_file}")
    
    def preview_toc(self):
        """预览生成的目录"""
        print("生成的目录预览：\n")
        print(self._generate_toc())


# ============ 使用示例 ============

if __name__ == "__main__":
    # 获取待生成目录的markdown文档路径
    parser = argparse.ArgumentParser(description="Markdown TOC Generator")
    parser.add_argument("markdown_file", help="Path to the markdown file")
    args = parser.parse_args()

    # 示例 1: 预览目录
    generator = MarkdownTOCGenerator(args.markdown_file)
    generator.preview_toc()
    
    # 示例 2: 生成新文件(直接覆盖原文件)
    generator.save_with_toc(args.markdown_file, insert_after_line=0)

    # 示例 3: 提取所有标题
    print("\n所有标题：")
    for level, title in generator.headings:
        print(f"{'  ' * (level - 1)}L{level}: {title}")