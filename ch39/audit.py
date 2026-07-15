#!/usr/bin/env python3
"""
audit.py — Hybrid LLM + static analysis pipeline

Usage: python audit.py --model gpt-4 --path ./target_repo
"""
import argparse
import subprocess
import json
import tempfile
import os


def run_semgrep(path):
    """Run Semgrep on the target path."""
    result = subprocess.run(
        ['semgrep', '--config=auto', path, '--json'],
        capture_output=True, text=True
    )
    return json.loads(result.stdout)


def run_codeql(path):
    """Run CodeQL on the target path."""
    # Placeholder — requires CodeQL database setup
    print("[*] CodeQL analysis would run here")
    return {'results': []}


def triage_with_llm(findings, model):
    """Filter findings using LLM."""
    # In production: call OpenAI/Anthropic API
    confirmed = []
    for finding in findings:
        # LLM prompt construction and API call
        confirmed.append(finding)
    return confirmed


def main():
    parser = argparse.ArgumentParser(
        description='Hybrid LLM + static analysis pipeline')
    parser.add_argument('--model', default='gpt-4',
                       help='LLM model for triage')
    parser.add_argument('--path', required=True,
                       help='Target repository path')
    args = parser.parse_args()

    print(f"[*] Stage 1: Static analysis on {args.path}")
    semgrep_results = run_semgrep(args.path)
    print(f"    Semgrep found {len(semgrep_results.get('results', []))} candidates")

    print(f"[*] Stage 2: LLM triage with {args.model}")
    refined = triage_with_llm(
        semgrep_results.get('results', []), args.model)
    print(f"    LLM filtered to {len(refined)} confirmed findings")

    print(f"[*] Stage 3: Human review required for {len(refined)} findings")
    for r in refined:
        loc = r.get('location', {})
        print(f"    - {loc.get('file', '?')}:{loc.get('line', '?')}")


if __name__ == "__main__":
    main()
