import 'package:flutter/material.dart';

enum TextStyleVariant {
  displayLarge,
  displayMedium,
  displaySmall,
  headlineLarge,
  headlineMedium,
  headlineSmall,
  titleLarge,
  titleMedium,
  titleSmall,
  bodyLarge,
  bodyMedium,
  bodySmall,
  labelLarge,
  labelMedium,
  labelSmall,
}

enum ColorVariant {
  primary,
  onPrimary,
  secondary,
  onSecondary,
  surface,
  onSurface,
  error,
  onError,
  surfaceContainerHighest,
  onSurfaceVariant,
}

class StyledText extends StatelessWidget {
  final String text;
  final TextStyleVariant variant;
  final ColorVariant colorVariant;

  const StyledText({
    super.key,
    required this.text,
    this.variant = TextStyleVariant.bodyLarge,
    this.colorVariant = ColorVariant.onSurface,
  });

  @override
  Widget build(BuildContext context) {
    final textTheme = Theme.of(context).textTheme;
    final colorScheme = Theme.of(context).colorScheme;

    TextStyle? getTextStyle() {
      switch (variant) {
        case TextStyleVariant.displayLarge:
          return textTheme.displayLarge;
        case TextStyleVariant.displayMedium:
          return textTheme.displayMedium;
        case TextStyleVariant.displaySmall:
          return textTheme.displaySmall;
        case TextStyleVariant.headlineLarge:
          return textTheme.headlineLarge;
        case TextStyleVariant.headlineMedium:
          return textTheme.headlineMedium;
        case TextStyleVariant.headlineSmall:
          return textTheme.headlineSmall;
        case TextStyleVariant.titleLarge:
          return textTheme.titleLarge;
        case TextStyleVariant.titleMedium:
          return textTheme.titleMedium;
        case TextStyleVariant.titleSmall:
          return textTheme.titleSmall;
        case TextStyleVariant.bodyLarge:
          return textTheme.bodyLarge;
        case TextStyleVariant.bodyMedium:
          return textTheme.bodyMedium;
        case TextStyleVariant.bodySmall:
          return textTheme.bodySmall;
        case TextStyleVariant.labelLarge:
          return textTheme.labelLarge;
        case TextStyleVariant.labelMedium:
          return textTheme.labelMedium;
        case TextStyleVariant.labelSmall:
          return textTheme.labelSmall;
      }
    }

    Color getColor() {
      switch (colorVariant) {
        case ColorVariant.primary:
          return colorScheme.primary;
        case ColorVariant.onPrimary:
          return colorScheme.onPrimary;
        case ColorVariant.secondary:
          return colorScheme.secondary;
        case ColorVariant.onSecondary:
          return colorScheme.onSecondary;
        case ColorVariant.surface:
          return colorScheme.surface;
        case ColorVariant.onSurface:
          return colorScheme.onSurface;
        case ColorVariant.error:
          return colorScheme.error;
        case ColorVariant.onError:
          return colorScheme.onError;
        case ColorVariant.surfaceContainerHighest:
          return colorScheme.surfaceContainerHighest;
        case ColorVariant.onSurfaceVariant:
          return colorScheme.onSurfaceVariant;
      }
    }

    return Text(
      text,
      style: getTextStyle()?.copyWith(color: getColor()),
    );
  }
}
