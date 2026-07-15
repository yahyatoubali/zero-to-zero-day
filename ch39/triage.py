#!/usr/bin/env python3
"""
triage.py — LLM triage pipeline for static analysis findings
Parses SARIF output from CodeQL/Semgrep and uses an LLM to classify findings.

Usage: python triage.py --sarif results.sarif --llm gpt-4
"""
import json
import argparse
import sys


def parse_sarif(sarif_path):
    """Extract findings from SARIF output."""
    with open(sarif_path) as f:
        data = json.load(f)

    findings = []
    for run in data.get('runs', []):
        for result in run.get('results', []):
            finding = {
                'rule_id': result.get('ruleId'),
                'message': result.get('message', {}).get('text', ''),
                'location': result.get('locations', [{}])[0]
                    .get('physicalLocation', {}),
                'severity': result.get('level', 'warning'),
            }

            loc = finding['location']
            finding['file'] = loc.get('artifactLocation', {}).get('uri', '')
            finding['line'] = loc.get('region', {}).get('startLine', 0)

            findings.append(finding)
    return findings


def build_prompt(finding):
    """Construct a structured prompt for LLM triage."""
    return f"""Analyze this static analysis finding and determine if it's a true vulnerability:

File: {finding['file']}:{finding['line']}
Rule: {finding['rule_id']}
Message: {finding['message']}

Is this a true vulnerability? Explain your reasoning and assign a confidence level (HIGH/MEDIUM/LOW)."""


def triage_findings(findings):
    """Placeholder triage — in production, call LLM API here."""
    for finding in findings:
        prompt = build_prompt(finding)
        # In production: response = openai.ChatCompletion.create(...)
        # For now, print the prompt
        print(f"\n=== Finding: {finding['file']}:{finding['line']} ===")
        print(prompt)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='LLM triage for SAST findings')
    parser.add_argument('--sarif', required=True, help='SARIF input file')
    parser.add_argument('--llm', default='gpt-4', help='LLM model to use')
    args = parser.parse_args()

    findings = parse_sarif(args.sarif)
    print(f"Parsed {len(findings)} findings from {args.sarif}")
    triage_findings(findings)
